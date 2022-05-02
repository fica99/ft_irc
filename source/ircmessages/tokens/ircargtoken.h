#pragma once

#include <string>

#include "ircmessages/tokens/irctoken.h"

namespace ircserv
{

class IRCArgToken : public IRCToken
{
public:
    IRCArgToken();
    virtual ~IRCArgToken();
private:
    void Initialize(void);
    void Shutdown(void);

public:

public:
    inline void SetArg(const std::string& arg) { m_Arg = arg; }
private:
    std::string m_Arg;
};

}

