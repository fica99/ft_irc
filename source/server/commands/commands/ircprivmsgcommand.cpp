#include "main/precomp.h"

#include "server/commands/commands/ircprivmsgcommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/responses/ircresponsesfactory.h"

namespace ircserv
{

IRCPrivmsgCommand::IRCPrivmsgCommand() : IRCCommand(Enum_IRCCommands_Privmsg)
{
    Initialize();
}

void IRCPrivmsgCommand::Initialize(void)
{
}

IRCPrivmsgCommand::~IRCPrivmsgCommand()
{
    Shutdown();
}

void IRCPrivmsgCommand::Shutdown(void)
{
}

bool IRCPrivmsgCommand::ProcessCommand(Server *serv)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCPrivmsgCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.empty())
    {

        return false;
    }
    return true;
}

}
