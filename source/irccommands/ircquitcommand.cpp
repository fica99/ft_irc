#include "main/precomp.h"

#include "irccommands/ircquitcommand.h"
#include "irccommands/irccommands.h"

#include "ircresponses/ircresponsesfactory.h"

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

bool IRCQuitCommand::ProcessCommand(void)
{
    if (ValidateArgs())
    {
        // serv->quitCommand();
        return true;
    }
    return false;
}

bool IRCQuitCommand::ValidateArgs(void)
{
    // if (!m_Args.empty())
    // {
    //     SetQuitMessage(m_Args[0]);
    // }
    return true;
}

}
