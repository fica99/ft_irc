#include "main/precomp.h"

#include "ircserver/ircsocket.h"
#include "utils/memory.h"
#include <fcntl.h>
#define LISTEN_QUEUE 128
#define RECV_BUF 512

namespace ircserv
{

IRCSocket::IRCSocket()
{
    Initialize();
}

IRCSocket::IRCSocket(int sockFd)
{
    Initialize();
    SetSockFd(sockFd);
    SetIsSockOpened(true);
}

void IRCSocket::Initialize(void)
{
    m_IsSockOpened = false;
}

IRCSocket::~IRCSocket()
{
    Shutdown();
}

void IRCSocket::Shutdown(void)
{
    if (GetIsSockOpened() == true)
    {
        CloseSocket();
    }
}

static int Getaddrinfo(const char *port, struct addrinfo** servInfo)
{
    struct addrinfo addressInfo;
    int status;

    memset(&addressInfo, 0, sizeof(addressInfo));
    addressInfo.ai_family = AF_UNSPEC;
    addressInfo.ai_socktype = SOCK_STREAM;
    addressInfo.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo(NULL, port, &addressInfo, servInfo)) != 0)
    {
        IRC_LOGE("getaddrinfo error: %s", gai_strerror(status));
    }
    return status;
}

static void Freeaddrinfo(struct addrinfo* servInfo)
{
    if (servInfo)
    {
        freeaddrinfo(servInfo);
    }
}

static int Socket(int domain, int type, int protocol)
{
    int status;

    status = socket(domain, type, protocol);
    if (status < 0)
    {
        IRC_LOGE("socket error: %s", strerror(errno));
    }
    return status;
}

static int Setsockopt(int sockFd, int level, int optname)
{
    static int optVal = 1;
    static unsigned int len = sizeof(optVal);
 
    int status = setsockopt(sockFd, level, optname, &optVal, len);
    if (status < 0)
    {
        IRC_LOGE("setsockopt error: %s", strerror(errno));
    }
    return status;
}

static int Bind(int sockFd, const struct sockaddr *address, socklen_t addressLen)
{
    int status;

    status = bind(sockFd, address, addressLen);
    if (status < 0)
    {
        IRC_LOGE("bind error: %s", strerror(errno));
    }
    return status;
}

bool IRCSocket::CreateListenSocket(uint16_t port)
{
    std::string portStr = std::to_string(port);
    struct addrinfo *servInfo, *p;

    if (GetIsSockOpened() == true)
    {
        return false;
    }

    if (Getaddrinfo(portStr.c_str(), &servInfo) != 0)
    {
        return false;
    }

    for (p = servInfo; p != NULL; p = p->ai_next)
    {
        int sockFd = Socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockFd == -1)
        {
            continue;
        }

        SetSockFd(sockFd);
        SetIsSockOpened(true);

        if (Setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR) == -1)
        {
            CloseSocket();
            Freeaddrinfo(servInfo);
            return false;
        }

        if (Bind(sockFd, p->ai_addr, p->ai_addrlen) == -1)
        {
            CloseSocket();
            continue;
        }
        break;
    }

    if (p == NULL)
    {
        IRC_LOGE("server: %s", "failed to create socket");
        Freeaddrinfo(servInfo);
        CloseSocket();
        return false;
    }

    Freeaddrinfo(servInfo);
	fcntl(GetSockFd(), F_SETFL, fcntl(GetSockFd(), F_GETFL, 0) | O_NONBLOCK);
    if (listen(GetSockFd(), LISTEN_QUEUE) != 0)
    {
        IRC_LOGE("listen error: %s", strerror(errno));
        CloseSocket();
        return false;
    }

    return true;
}

void IRCSocket::CloseSocket(void)
{
    if (GetIsSockOpened() == false)
    {
        return;
    }

    SetIsSockOpened(false);
    close(GetSockFd());
}

IRCSocket *IRCSocket::Accept(void)
{
    struct sockaddr_storage acceptAddrInfo;
    static socklen_t addrInfoSize = sizeof(acceptAddrInfo);
    IRCSocket *acceptedSocket = NULL;

    int acceptedSockFd = accept(GetSockFd(), (struct sockaddr *)&acceptAddrInfo, &addrInfoSize);
    if (acceptedSockFd < 0)
    {
        IRC_LOGE("accept error: %s", strerror(errno));
        return NULL;
    }
    IRC_LOGI("%s", "Accepted new connection");
    return New(IRCSocket)(acceptedSockFd);
}

int IRCSocket::Send(const std::string& msg)
{
    size_t total = 0;
    size_t bytesleft = msg.size();
    int n;

    while(total < msg.size())
    {
        n = send(GetSockFd(), msg.c_str() + total, bytesleft, 0);
        if (n == -1)
        {
            IRC_LOGE("send error: %s", strerror(errno));
            break;
        }
        total += n;
        bytesleft -= n;
    }
    if (n != -1)
    {
        IRC_LOGI("%s", "Message sent");
    }
    IRC_LOGD("Total bytes sent: %d, bytes left: %d", total, bytesleft);
    return (n == -1) ? -1 : 0;
}

int IRCSocket::Recv(std::string& msg)
{
    char buff[RECV_BUF + 1];

    int nbytes = recv(GetSockFd(), buff, RECV_BUF, 0);
    if (nbytes < 0)
    {
        IRC_LOGE("recv error: %s", strerror(errno));
    }
    else
    {
        buff[nbytes] = '\0';
        msg.assign(buff);
        IRC_LOGI("%s", "Message received");
        IRC_LOGD("Total bytes received: %d", nbytes);
    }
    return nbytes;
}


static void RemoveNotSelectedSockets(fd_set& fdSet, std::vector<IRCSocket*>& sockets)
{
    for (std::vector<IRCSocket*>::iterator it = sockets.begin(); it != sockets.end(); )
    {
        if (FD_ISSET((*it)->GetSockFd(), &fdSet) == false)
        {
            it = sockets.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

static int FillFdSet(fd_set& fdSet, const std::vector<IRCSocket*>& sockets)
{
    int fdMax = 0;

    FD_ZERO(&fdSet);
    for (size_t i = 0; i < sockets.size(); ++i)
    {
        int sockFd = sockets[i]->GetSockFd();
        fdMax = std::max(fdMax, sockFd);
        FD_SET(sockFd, &fdSet);
    }
    return fdMax;
}

int IRCSocket::Select(std::vector<IRCSocket*>& sockets, int delaySec)
{
    int result = 0;

    if (!sockets.empty())
    {
        fd_set fdSet;
        int fdMax = FillFdSet(fdSet, sockets);
        struct timeval tv;

        tv.tv_sec = delaySec;
        tv.tv_usec = 0;

        result = select(fdMax + 1, &fdSet, NULL, NULL, &tv);
        if (result < 0)
        {
            IRC_LOGE("select error: %s", strerror(errno));
        }
        else if (result > 0)
        {
            RemoveNotSelectedSockets(fdSet, sockets);
            IRC_LOGD("Selected %d sockets", result);
        }
    }

    return result;
}

void IRCSocket::SetSockFd_Callback(int sockFd)
{
    if (sockFd == m_SockFd)
    {
        return;
    }

    if (GetIsSockOpened() == true)
    {
        CloseSocket();
    }
    m_SockFd = sockFd;
}

void IRCSocket::SetIsSockOpened_Callback(bool isSockOpened)
{
    if (isSockOpened == m_IsSockOpened)
    {
        return;
    }

    if (isSockOpened == true)
    {
        IRC_LOGD("Socket %d is opened", GetSockFd());
    }
    else
    {
        IRC_LOGD("Socket %d is closed", GetSockFd());
    }
    m_IsSockOpened = isSockOpened;
}



}
