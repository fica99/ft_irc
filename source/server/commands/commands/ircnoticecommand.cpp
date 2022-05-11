#include "main/precomp.h"

#include "server/commands/commands/ircnoticecommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/parsing/ircparsinghelper.h"
#include "server/commands/responses/ircresponsesfactory.h"

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

bool IRCNoticeCommand::ProcessCommand(Server *serv)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCNoticeCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.size() < 2)
    {
        return false;
    }
    else
    {
        if (!IRCParsingHelper::IsNick(m_Args[0]))
        {
            return false;
        }
        SetNickname(m_Args[0]);
        SetText(m_Args[1]);
    }
    return true;
}
}
