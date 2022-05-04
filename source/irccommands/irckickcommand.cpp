#include "main/precomp.h"

#include "irccommands/irckickcommand.h"

#include "irccommands/irccommands.h"
#include "ircresponses/ircresponsesfactory.h"

namespace ircserv
{

IRCKickCommand::IRCKickCommand() : IRCCommand(Enum_IRCCommands_Kick)
{
    Initialize();
}

void IRCKickCommand::Initialize(void)
{
}

IRCKickCommand::~IRCKickCommand()
{
    Shutdown();
}

void IRCKickCommand::Shutdown(void)
{
}

bool IRCKickCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCKickCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.empty())
    {

        return false;
    }
    return true;
}
}
