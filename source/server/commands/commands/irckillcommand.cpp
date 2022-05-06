#include "main/precomp.h"

#include "server/commands/commands/irckillcommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/responses/ircresponsesfactory.h"

namespace ircserv
{

IRCKillCommand::IRCKillCommand() : IRCCommand(Enum_IRCCommands_Kill)
{
    Initialize();
}

void IRCKillCommand::Initialize(void)
{
}

IRCKillCommand::~IRCKillCommand()
{
    Shutdown();
}

void IRCKillCommand::Shutdown(void)
{
}

bool IRCKillCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCKillCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.empty())
    {

        return false;
    }
    return true;
}
}
