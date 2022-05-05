#include "main/precomp.h"

#include "commands/irclistcommand.h"

#include "commands/irccommands.h"
#include "responses/ircresponsesfactory.h"

namespace ircserv
{

IRCListCommand::IRCListCommand() : IRCCommand(Enum_IRCCommands_List)
{
    Initialize();
}

void IRCListCommand::Initialize(void)
{
}

IRCListCommand::~IRCListCommand()
{
    Shutdown();
}

void IRCListCommand::Shutdown(void)
{
}

bool IRCListCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCListCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.empty())
    {

        return false;
    }
    return true;
}
}
