#include "main/precomp.h"

#include "ircserver/ircsocket.h"

#define LISTEN_QUEUE 128

namespace ircserv
{

IRCSocket::IRCSocket()
{
    Initialize();
}

void IRCSocket::Initialize(void)
{
}

IRCSocket::~IRCSocket()
{
    Shutdown();
}

void IRCSocket::Shutdown(void)
{
}

bool IRCSocket::CreateListenSocket(uint16_t port)
{
    struct addrinfo *servInfo, *p;
    std::string portStr;
    std::stringstream out;
    int optVal = 1;

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
        if ((m_SockFd = Socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            continue;
        }
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
        return false;
    }

    freeaddrinfo(servInfo);

    if (listen(m_SockFd, LISTEN_QUEUE) != 0)
    {
        IRC_LOGE("listen error: %s", strerror(errno));
        CloseSocket();
        return false;
    }

    IRC_LOGD("Server socket created, binded and listens! FD: %d", m_SockFd);

    return true;
}

void IRCSocket::CloseSocket(void)
{
    close(m_SockFd);
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
    int status = setsockopt(m_SockFd, level, optname, optval, len);
    if (status < 0)
    {
        IRC_LOGE("setsockopt error: %s", strerror(errno));
    }
    return status;
}

int IRCSocket::Bind(const struct sockaddr *address, socklen_t addressLen)
{
    int status;

    status = bind(m_SockFd, address, addressLen);
    if (status < 0)
    {
        IRC_LOGE("bind error: %s", strerror(errno));
    }
    return status;
}

}
