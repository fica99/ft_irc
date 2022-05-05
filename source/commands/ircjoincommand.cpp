#include "main/precomp.h"

#include "commands/ircjoincommand.h"

#include "commands/irccommands.h"
#include "responses/ircresponsesfactory.h"

namespace ircserv
{

IRCJoinCommand::IRCJoinCommand() : IRCCommand(Enum_IRCCommands_Join)
{
    Initialize();
}

void IRCJoinCommand::Initialize(void)
{
}

IRCJoinCommand::~IRCJoinCommand()
{
    Shutdown();
}

void IRCJoinCommand::Shutdown(void)
{
}

bool IRCJoinCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCJoinCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.empty())
    {

        return false;
    }
    return true;
}
}
