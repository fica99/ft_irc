#pragma once

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

namespace ircserv
{

class IRCSocket
{
public:
    IRCSocket();
    virtual ~IRCSocket();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool CreateListenSocket(uint16_t port);
    void CloseSocket(void);

private:
    int Getaddrinfo(const char *port, struct addrinfo** servInfo);
    void Freeaddrinfo(struct addrinfo* servInfo);
    int Socket(int domain, int type, int protocol);
    int Setsockopt(int level, int optname, void* optval);
    int Bind(const struct sockaddr *address, socklen_t addressLen);

private:
    struct addrinfo m_AddressInfo;
    int m_SockFd;
};

}
