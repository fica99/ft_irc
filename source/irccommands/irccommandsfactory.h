#pragma once

#include <string>
#include <vector>

#include "irccommands/irccommand.h"
#include "irccommands/irccommands.h"

namespace ircserv
{

class IRCCommandsFactory
{
public:
    IRCCommandsFactory();
    virtual ~IRCCommandsFactory();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    IRCCommand* CreateCommand(Enum_IRCCommands commandType);
    void DestroyCommand(IRCCommand* command);
};

}
