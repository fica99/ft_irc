#include "main/precomp.h"

#include "irccommands/ircpartcommand.h"

#include "irccommands/irccommands.h"
#include "ircresponses/ircresponsesfactory.h"

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

bool IRCPartCommand::ProcessCommand(/*serverclass */)
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
