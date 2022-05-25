#include "main/precomp.h"

#include "irccommands/ircnoticecommand.h"
#include "irccommands/irccommands.h"

#include "parsing/ircparsinghelper.h"
#include "ircresponses/ircresponsesfactory.h"

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

bool IRCNoticeCommand::ProcessCommand(IRCSocket *socket)
{
    if (ValidateArgs(socket))
    {
        return true;
    }
    return false;
}

bool IRCNoticeCommand::ValidateArgs(IRCSocket *socket)
{
    // if (m_Args.size() < 2)
    // {
    //     return false;
    // }
    // else
    // {
    //     if (!IRCParsingHelper::IsNick(m_Args[0]))
    //     {
    //         return false;
    //     }
    //     SetNickname(m_Args[0]);
    //     SetText(m_Args[1]);
    // }
    return true;
}
}
