#include "main/precomp.h"

#include "irccommands/ircpasscommand.h"

#include "irccommands/irccommands.h"


namespace ircserv
{

IRCPassCommand::IRCPassCommand()
{
    Initialize();
}

void IRCPassCommand::Initialize(void)
{
    SetCommandType(Enum_IRCCommands_Pass);
}

IRCPassCommand::~IRCPassCommand()
{
    Shutdown();
}

void IRCPassCommand::Shutdown(void)
{
}

bool IRCPassCommand::ProcessCommand(/*serverclass */)
{
    return true;
}


}
