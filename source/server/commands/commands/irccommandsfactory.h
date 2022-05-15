#pragma once

#include <string>
#include <vector>

#include "server/commands/commands/irccommands.h"

namespace ircserv
{

class IRCCommand;
class IRCCommandsFactory
{
public:
    IRCCommandsFactory();
    virtual ~IRCCommandsFactory();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    IRCCommand* CreateCommand(Enum_IRCCommands commandType = Enum_IRCCommands_Unknown);
    void DestroyCommand(IRCCommand* command);
};

}
