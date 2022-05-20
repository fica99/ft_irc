#include "main/precomp.h"

#include "irccommands/ircnamescommand.h"
#include "irccommands/irccommands.h"

#include "parsing/ircparsinghelper.h"
#include "ircresponses/ircresponsesfactory.h"

namespace ircserv
{

IRCNamesCommand::IRCNamesCommand() : IRCCommand(Enum_IRCCommands_Names)
{
    Initialize();
}

void IRCNamesCommand::Initialize(void)
{
}

IRCNamesCommand::~IRCNamesCommand()
{
    Shutdown();
}

void IRCNamesCommand::Shutdown(void)
{
}

bool IRCNamesCommand::ProcessCommand(void)
{
    if (ValidateArgs())
    {
        return true;
    }
    return false;
}

bool IRCNamesCommand::ValidateArgs(void)
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
