#pragma once

#include <string>
#include <vector>

#include "server/commands/commands/irccommand.h"
#include "server/commands/commands/irccommands.h"
#include "server/commands/commands/irccommandsfactory.h"
#include "server/commands/parsing/tokens/irccommandtoken.h"
#include "server/commands/parsing/tokens/irctoken.h"

namespace ircserv
{

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
    IRCCommandsFactory m_CommandsFactory;
};

}
