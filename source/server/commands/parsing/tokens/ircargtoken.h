#pragma once

#include <string>

#include "server/commands/parsing/tokens/irctoken.h"

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
    inline const std::string& GetArg(void) const { return m_Arg; }
private:
    std::string m_Arg;
};

}

