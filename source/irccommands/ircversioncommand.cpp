#include "main/precomp.h"

#include "irccommands/ircversioncommand.h"

#include "irccommands/irccommands.h"
#include "ircresponses/ircresponsesfactory.h"

namespace ircserv
{

IRCVersionCommand::IRCVersionCommand() : IRCCommand(Enum_IRCCommands_Version)
{
    Initialize();
}

void IRCVersionCommand::Initialize(void)
{
}

IRCVersionCommand::~IRCVersionCommand()
{
    Shutdown();
}

void IRCVersionCommand::Shutdown(void)
{
}

bool IRCVersionCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCVersionCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.empty())
    {

        return false;
    }
    return true;
}

}
