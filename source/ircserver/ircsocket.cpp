#include "main/precomp.h"

#include "ircserver/ircsocket.h"
#include "utils/memory.h"

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
    SetSockFd(sockFd);
    SetIsSockOpened(true);
}

void IRCSocket::Initialize(void)
{
    SetIsSockOpened(false);
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

bool IRCSocket::CreateListenSocket(uint16_t port)
{
    std::string portStr = std::to_string(port);
    struct addrinfo *servInfo, *p;

    if (GetIsSockOpened() == true)
    {
        IRC_LOGD("%s", "Socket is already opened");
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

        if (Setsockopt(SOL_SOCKET, SO_REUSEADDR) == -1)
        {
            CloseSocket();
            Freeaddrinfo(servInfo);
            return false;
        }

        if (Bind(p->ai_addr, p->ai_addrlen) == -1)
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
        return false;
    }

    Freeaddrinfo(servInfo);

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
    IRC_LOGD("Total bytes sent: %d", total);
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
        IRC_LOGD("Total bytes received: %d", nbytes);
    }
    return nbytes;
}


static void ProccessSelectedSockets(fd_set& fdSet, std::vector<IRCSocket*>& sockets)
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
            ProccessSelectedSockets(fdSet, sockets);
        }
    }

    return result;
}

int IRCSocket::Getaddrinfo(const char *port, struct addrinfo** servInfo)
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

void IRCSocket::Freeaddrinfo(struct addrinfo* servInfo)
{
    if (servInfo)
    {
        freeaddrinfo(servInfo);
    }
}

int IRCSocket::Socket(int domain, int type, int protocol)
{
    int status;

    status = socket(domain, type, protocol);
    if (status < 0)
    {
        IRC_LOGE("socket error: %s", strerror(errno));
    }
    return status;
}

int IRCSocket::Setsockopt(int level, int optname)
{
    static int optVal = 1;
    static unsigned int len = sizeof(optVal);
 
    int status = setsockopt(GetSockFd(), level, optname, &optVal, len);
    if (status < 0)
    {
        IRC_LOGE("setsockopt error: %s", strerror(errno));
    }
    return status;
}

int IRCSocket::Bind(const struct sockaddr *address, socklen_t addressLen)
{
    int status;

    status = bind(GetSockFd(), address, addressLen);
    if (status < 0)
    {
        IRC_LOGE("bind error: %s", strerror(errno));
    }
    return status;
}

void IRCSocket::SetSockFd_Callback(int sockFd)
{
    if (GetIsSockOpened() == true)
    {
        CloseSocket();
    }
    m_SockFd = sockFd;
    SetIsSockOpened(true);
}

void IRCSocket::SetIsSockOpened_Callback(bool isSockOpened)
{
    if (isSockOpened == m_IsSockOpened)
    {
        return;
    }

    if (isSockOpened == true)
    {
        IRC_LOGD("%s", "Socket is opened");
    }
    else
    {
        IRC_LOGD("%s", "Socket is closed");
    }
    m_IsSockOpened = isSockOpened;
}



}
