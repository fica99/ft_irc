#include "main/precomp.h"

#include "commands/ircnamescommand.h"

#include "commands/irccommands.h"
#include "responses/ircresponsesfactory.h"

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

bool IRCNamesCommand::ProcessCommand(/*serverclass */)
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
