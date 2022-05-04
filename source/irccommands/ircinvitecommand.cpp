#include "main/precomp.h"

#include "irccommands/ircinvitecommand.h"

#include "irccommands/irccommands.h"
#include "ircresponses/ircresponsesfactory.h"

namespace ircserv
{

IRCInviteCommand::IRCInviteCommand() : IRCCommand(Enum_IRCCommands_Invite)
{
    Initialize();
}

void IRCInviteCommand::Initialize(void)
{
}

IRCInviteCommand::~IRCInviteCommand()
{
    Shutdown();
}

void IRCInviteCommand::Shutdown(void)
{
}

bool IRCInviteCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCInviteCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.empty())
    {

        return false;
    }
    return true;
}
}
