#pragma once

#include <string>
#include <vector>

#include "irccommands/irccommand.h"
#include "irccommands/irccommands.h"
#include "parsing/tokens/irccommandtoken.h"
#include "parsing/tokens/irctoken.h"

namespace ircserv
{

class IRCCommand;

class IRCParser
{
public:
    IRCParser();
    virtual ~IRCParser();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    IRCCommand* CreateCommand(const std::vector<IRCToken*>& tokens);
    void DestroyCommand(IRCCommand* command);
private:
    Enum_IRCCommands GetCommandEnum(IRCCommandToken *commandToken);
    std::vector<std::string> GetArgs(const std::vector<IRCToken*>& tokens);
private:
};

}
