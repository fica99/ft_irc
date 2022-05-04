#include "main/precomp.h"

#include "irccommands/irctimecommand.h"

#include "irccommands/irccommands.h"
#include "ircresponses/ircresponsesfactory.h"

namespace ircserv
{

IRCTimeCommand::IRCTimeCommand() : IRCCommand(Enum_IRCCommands_Time)
{
    Initialize();
}

void IRCTimeCommand::Initialize(void)
{
}

IRCTimeCommand::~IRCTimeCommand()
{
    Shutdown();
}

void IRCTimeCommand::Shutdown(void)
{
}

bool IRCTimeCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCTimeCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.empty())
    {

        return false;
    }
    return true;
}

}
