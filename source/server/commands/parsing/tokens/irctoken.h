#pragma once

namespace ircserv
{

class IRCToken
{
public:
    IRCToken();
    virtual ~IRCToken();
private:
    void Initialize(void);
    void Shutdown(void);
};

}
