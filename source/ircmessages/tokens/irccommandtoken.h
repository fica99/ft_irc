#pragma once

#include <string>

#include "irccommands/irccommands.h"
#include "ircmessages/tokens/irctoken.h"

namespace ircserv
{

class IRCCommandToken : public IRCToken
{
public:
    IRCCommandToken(const std::string& rawStr);
    virtual ~IRCCommandToken();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    inline Enum_IRCCommands GetCommandEnum(void) const { return m_CommandEnum; }

private:
    Enum_IRCCommands m_CommandEnum;
};

}
