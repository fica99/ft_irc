#include "main/precomp.h"

#include "irccommands/ircnickcommand.h"

#include "irccommands/irccommands.h"


namespace ircserv
{

IRCNickCommand::IRCNickCommand()
{
    Initialize();
}

void IRCNickCommand::Initialize(void)
{
    SetCommandType(Enum_IRCCommands_Nick);
}

IRCNickCommand::~IRCNickCommand()
{
    Shutdown();
}

void IRCNickCommand::Shutdown(void)
{
}

bool IRCNickCommand::ProcessCommand(/*serverclass */)
{
    return true;
}


}
