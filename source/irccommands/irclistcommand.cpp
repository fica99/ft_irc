#include "main/precomp.h"

#include "irccommands/irclistcommand.h"
#include "irccommands/irccommands.h"

#include "parsing/ircparsinghelper.h"
#include "ircresponses/ircresponsesfactory.h"

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

bool IRCListCommand::ProcessCommand(void)
{
    if (ValidateArgs())
    {
        return true;
    }
    return false;
}

bool IRCListCommand::ValidateArgs(void)
{
    // if (!m_Args.empty())
    // {
    //     if (!IRCParsingHelper::IsChannels(m_Args[0]))
    //     {
    //         return false;
    //     }
    //     SetChannels(IRCParsingHelper::Split(m_Args[0], ","));
    // }
    return true;
}
}
