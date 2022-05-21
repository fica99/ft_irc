#pragma once

namespace ircserv
{

class IRCClient
{
public:
    IRCClient();
    virtual ~IRCClient();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    void SetFd(int fd) { m_Fd = fd; }

private:
    int m_Fd;
};


}
