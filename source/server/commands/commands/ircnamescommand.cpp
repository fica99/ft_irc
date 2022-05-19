#include "main/precomp.h"

#include "server/commands/commands/ircnamescommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/parsing/ircparsinghelper.h"
#include "server/commands/responses/ircresponsesfactory.h"

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

bool IRCNamesCommand::ProcessCommand(IRCServer *serv)
{
    if (ValidateArgs(serv))
    {
        return true;
    }
    return false;
}

bool IRCNamesCommand::ValidateArgs(IRCServer *serv)
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