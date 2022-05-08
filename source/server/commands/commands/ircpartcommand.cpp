#include "main/precomp.h"

#include "server/commands/commands/ircpartcommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/responses/ircresponsesfactory.h"

namespace ircserv
{

IRCPartCommand::IRCPartCommand() : IRCCommand(Enum_IRCCommands_Part)
{
    Initialize();
}

void IRCPartCommand::Initialize(void)
{
}

IRCPartCommand::~IRCPartCommand()
{
    Shutdown();
}

void IRCPartCommand::Shutdown(void)
{
}

bool IRCPartCommand::ProcessCommand(Server *serv)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCPartCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.empty())
    {
        return false;
    }
    return true;
}
}
