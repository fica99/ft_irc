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
    int Recv(std::string& msg);
    int Send(const std::string& msg);

public:
    static int Select(std::vector<IRCSocket*>& sockets, int delaySec);

private:
    void SetSockFd_Callback(int sockFd);
    void SetIsSockOpened_Callback(bool isSockOpened);

public:
    inline void SetIsSockOpened(bool isSockOpened) { SetIsSockOpened_Callback(isSockOpened); }
    inline bool GetIsSockOpened(void) const { return m_IsSockOpened; }
    inline void SetSockFd(int sockFd) { SetSockFd_Callback(sockFd); }
    inline int GetSockFd(void) const { return m_SockFd; }

private:
    bool m_IsSockOpened;
    int m_SockFd;
};

}
