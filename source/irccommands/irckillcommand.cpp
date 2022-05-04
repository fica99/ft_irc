#include "main/precomp.h"

#include "irccommands/irckillcommand.h"

#include "irccommands/irccommands.h"
#include "ircresponses/ircresponsesfactory.h"

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
