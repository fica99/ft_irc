#include "main/precomp.h"

#include "server/commands/commands/ircquitcommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/responses/ircresponsesfactory.h"

namespace ircserv
{

IRCQuitCommand::IRCQuitCommand() : IRCCommand(Enum_IRCCommands_Quit)
{
    Initialize();
}

void IRCQuitCommand::Initialize(void)
{
}

IRCQuitCommand::~IRCQuitCommand()
{
    Shutdown();
}

void IRCQuitCommand::Shutdown(void)
{
}

bool IRCQuitCommand::ProcessCommand(IRCServer *serv)
{
    if (ValidateArgs(serv))
    {
        return true;
    }
    return false;
}

bool IRCQuitCommand::ValidateArgs(IRCServer *serv)
{
    if (!m_Args.empty())
    {
        SetQuitMessage(m_Args[0]);
    }
    return true;
}

}
