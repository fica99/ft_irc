#include "main/precomp.h"

#include "server/commands/commands/irclistcommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/parsing/ircparsinghelper.h"
#include "server/commands/responses/ircresponsesfactory.h"

namespace ircserv
{

IRCListCommand::IRCListCommand() : IRCCommand(Enum_IRCCommands_List)
{
    Initialize();
}

void IRCListCommand::Initialize(void)
{
}

IRCListCommand::~IRCListCommand()
{
    Shutdown();
}

void IRCListCommand::Shutdown(void)
{
}

bool IRCListCommand::ProcessCommand(Server *serv)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCListCommand::ValidateArgs(/*serverclass */)
{
    if (!m_Args.empty())
    {
        if (!IRCParsingHelper::IsChannels(m_Args[0]))
        {
            return false;
        }
        SetChannels(IRCParsingHelper::Split(m_Args[0], ","));
    }
    return true;
}
}
