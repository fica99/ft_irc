#pragma once

#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

namespace ircserv
{

class IRCSocket
{
public:
    IRCSocket();
    IRCSocket(int sockFd);
    virtual ~IRCSocket();

private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool CreateListenSocket(uint16_t port);
    void CloseSocket(void);
    IRCSocket *Accept(void);

public:
    static int Select(std::vector<IRCSocket*>& sockets, int delaySec);

private:
    int Getaddrinfo(const char *port, struct addrinfo** servInfo);
    void Freeaddrinfo(struct addrinfo* servInfo);
    int Socket(int domain, int type, int protocol);
    int Setsockopt(int level, int optname);
    int Bind(const struct sockaddr *address, socklen_t addressLen);

public:
    inline int GetSockFd(void) const { return m_SockFd; }
    inline bool GetIsSockOpened(void) const { return m_IsSockOpened; }

private:
    void SetSockFd_Callback(int sockFd);

private:
    inline void SetSockFd(int sockFd) { SetSockFd_Callback(sockFd); }
    inline void SetIsSockOpened(bool isSockOpened) { m_IsSockOpened = isSockOpened; }

private:
    bool m_IsSockOpened;
    int m_SockFd;
};

}
