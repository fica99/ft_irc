#include "main/precomp.h"

#include "irccommands/ircprivmsgcommand.h"

#include "irccommands/irccommands.h"
#include "ircresponses/ircresponsesfactory.h"

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

bool IRCPrivmsgCommand::ProcessCommand(/*serverclass */)
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
