#include "main/precomp.h"

#include "irccommands/ircmodecommand.h"

#include "irccommands/irccommands.h"
#include "ircresponses/ircresponsesfactory.h"

namespace ircserv
{

IRCModeCommand::IRCModeCommand() : IRCCommand(Enum_IRCCommands_Mode)
{
    Initialize();
}

void IRCModeCommand::Initialize(void)
{
}

IRCModeCommand::~IRCModeCommand()
{
    Shutdown();
}

void IRCModeCommand::Shutdown(void)
{
}

bool IRCModeCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCModeCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.empty())
    {

        return false;
    }
    return true;
}
}
