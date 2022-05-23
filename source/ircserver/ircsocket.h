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
    IRCSocket(uint16_t port, const std::string address, int sockFd);

    virtual ~IRCSocket();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool CreateListenSocket(uint16_t port);
    void CloseSocket(void);
    IRCSocket *Accept(void);
    static int Select(std::vector<IRCSocket*>& reads, int delaySec);

private:
    int Getaddrinfo(const char *port, struct addrinfo** servInfo);
    void Freeaddrinfo(struct addrinfo* servInfo);
    int Socket(int domain, int type, int protocol);
    int Setsockopt(int level, int optname, void* optval);
    int Bind(const struct sockaddr *address, socklen_t addressLen);
   

public:
    inline int GetSockFd(void) const { return m_SockFd; }
    inline bool GetIsSockOpened(void) const { return m_IsSockOpened; }
    inline uint16_t GetPort(void) { return m_Port; }
    inline const std::string& GetAddress(void) const { return m_Address; }

private:
    inline void SetSockFd(int sockFd) { m_SockFd = sockFd; }
    inline void SetIsSockOpened(bool isOpened) { m_IsSockOpened = isOpened; }
    inline void SetPort(uint16_t port) { m_Port = port; }
    inline void SetAddress(const std::string& address) { m_Address = address; }

private:
    struct addrinfo m_AddressInfo;
    int m_SockFd;
    bool m_IsSockOpened;
    uint16_t m_Port;
    std::string m_Address;

};

}
