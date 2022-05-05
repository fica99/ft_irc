#include "main/precomp.h"

#include "commands/ircnoticecommand.h"

#include "commands/irccommands.h"
#include "responses/ircresponsesfactory.h"

namespace ircserv
{

IRCNoticeCommand::IRCNoticeCommand() : IRCCommand(Enum_IRCCommands_Notice)
{
    Initialize();
}

void IRCNoticeCommand::Initialize(void)
{
}

IRCNoticeCommand::~IRCNoticeCommand()
{
    Shutdown();
}

void IRCNoticeCommand::Shutdown(void)
{
}

bool IRCNoticeCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCNoticeCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.empty())
    {
        return false;
    }
    return true;
}
}
