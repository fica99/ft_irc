#include "main/precomp.h"

#include "server/commands/commands/ircnamescommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/responses/ircresponsesfactory.h"

namespace ircserv
{

IRCNamesCommand::IRCNamesCommand() : IRCCommand(Enum_IRCCommands_Names)
{
    Initialize();
}

void IRCNamesCommand::Initialize(void)
{
}

IRCNamesCommand::~IRCNamesCommand()
{
    Shutdown();
}

void IRCNamesCommand::Shutdown(void)
{
}

bool IRCNamesCommand::ProcessCommand(Server *serv)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCNamesCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.empty())
    {

        return false;
    }
    return true;
}
}
