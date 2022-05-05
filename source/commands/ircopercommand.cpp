#include "main/precomp.h"

#include "commands/ircopercommand.h"

#include "commands/irccommands.h"
#include "responses/ircresponsesfactory.h"

namespace ircserv
{

IRCOperCommand::IRCOperCommand() : IRCCommand(Enum_IRCCommands_Oper)
{
    Initialize();
}

void IRCOperCommand::Initialize(void)
{
}

IRCOperCommand::~IRCOperCommand()
{
    Shutdown();
}

void IRCOperCommand::Shutdown(void)
{
}

bool IRCOperCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCOperCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.empty())
    {
        return false;
    }
    return true;
}
}
