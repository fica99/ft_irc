#include "main/precomp.h"

#include "ircserver/ircsocket.h"
#include "utils/memory.h"

#define LISTEN_QUEUE 128

namespace ircserv
{

IRCSocket::IRCSocket()
{
    Initialize();
}

IRCSocket::IRCSocket(uint16_t port, const std::string address, int sockFd)
{
    Initialize();
    SetPort(port);
    SetAddress(address);
    SetSockFd(sockFd);
    SetIsSockOpened(true);
}

void IRCSocket::Initialize(void)
{
    SetSockFd(-1);
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
    if (m_IsSockOpened == true)
    {
        IRC_LOGD("Socket is already opened, please, close it before opening one more time. FD: %d", GetSockFd());
        return false;
    }

    struct addrinfo *servInfo, *p;
    int optVal = 1;
    int sockFd;
    std::string portStr;
    std::stringstream out;

    out << port;
    portStr = out.str();

    memset(&m_AddressInfo, 0, sizeof(m_AddressInfo));
    m_AddressInfo.ai_family = AF_UNSPEC;
    m_AddressInfo.ai_socktype = SOCK_STREAM;
    m_AddressInfo.ai_flags = AI_PASSIVE;

    if (Getaddrinfo(portStr.c_str(), &servInfo))
    {
        return false;
    }

    for (p = servInfo; p != NULL; p = p->ai_next)
    {
        if ((sockFd = Socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            continue;
        }
        SetSockFd(sockFd);
        SetIsSockOpened(true);
        if (Setsockopt(SOL_SOCKET, SO_REUSEADDR, &optVal) == -1)
        {
            CloseSocket();
            freeaddrinfo(servInfo);
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
        IRC_LOGE("server: %s", "failed to create socket, set socket options or bind ");
        freeaddrinfo(servInfo);
        return false;
    }

    freeaddrinfo(servInfo);

    if (listen(GetSockFd(), LISTEN_QUEUE) != 0)
    {
        IRC_LOGE("listen error: %s", strerror(errno));
        CloseSocket();
        return false;
    }

    IRC_LOGD("Server socket created, binded and listens! FD: %d", GetSockFd());
    return true;
}

void IRCSocket::CloseSocket(void)
{
    SetIsSockOpened(false);
    close(GetSockFd());
}

IRCSocket *IRCSocket::Accept(void)
{
    struct sockaddr_storage conAddrInfo;
    static socklen_t addrSize = sizeof(conAddrInfo);
    char host[NI_MAXHOST];
    IRCSocket *conSocket = NULL;

    int conSockFd = accept(GetSockFd(), (struct sockaddr *)&conAddrInfo, &addrSize);
    if (conSockFd < 0)
    {
        IRC_LOGE("accept error: %s", strerror(errno));
        return NULL;
    }
    
    int status = getnameinfo((struct sockaddr *)&conAddrInfo, addrSize, host, sizeof(host), NULL, 0, NI_NUMERICHOST);
    if (status < 0)
    {
        IRC_LOGE("getnameinfo error: %s", gai_strerror(errno));
    }
    else
    {
        conSocket = new IRCSocket(GetPort(), host, conSockFd);
    }
    return conSocket;
}

int IRCSocket::Select(std::vector<IRCSocket*>& reads, int delaySec)
{
    if (reads.empty())
    {
        return -1;
    }

    int listenSock = reads[0]->GetSockFd();
    struct timeval tv;
    fd_set readFds;

    tv.tv_sec = delaySec;
    tv.tv_usec = 0;
    
    FD_ZERO(&readFds);

    int maxSock = 0;
    for (size_t i = 0; i < reads.size(); ++i)
    {
        if (reads[i]->GetSockFd() > maxSock)
        {
            maxSock = reads[i]->GetSockFd();
        }
        FD_SET(reads[i]->GetSockFd(), &readFds);
    }

    int result = select(maxSock + 1, &readFds, NULL, NULL, &tv);
    
    if (result < 0)
    {
        IRC_LOGE("select error: %s", strerror(errno));
    }
    else if (result > 0)
    {
        for (std::vector<IRCSocket*>::iterator it = reads.begin(); it != reads.end(); )
        {
            if (FD_ISSET((*it)->GetSockFd(), &readFds) == false)
            {
                it = reads.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    return result;
}


int IRCSocket::Getaddrinfo(const char *port, struct addrinfo** servInfo)
{
    int status;

    if ((status = getaddrinfo(NULL, port, &m_AddressInfo, servInfo)) != 0)
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

int IRCSocket::Setsockopt(int level, int optname, void* optval)
{
    unsigned int len = sizeof(optval);
    int status = setsockopt(GetSockFd(), level, optname, optval, len);
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

}
