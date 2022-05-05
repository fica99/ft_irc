#pragma once

#include <string>
#include <vector>

#include "utils/singleton.h"
#include "server/commands/commands/irccommand.h"
#include "server/commands/commands/irccommands.h"

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
    DECLARE_SIMPLE_SINGLETON(IRCCommandsFactory);

public:
    IRCCommand* CreateCommand(Enum_IRCCommands commandType = Enum_IRCCommands_Unknown);
    void DestroyCommand(IRCCommand* command);
};

#define GetIRCCommandsFactory() IRCCommandsFactory::GetInstance()

}
