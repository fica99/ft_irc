#include "main/precomp.h"

#include "commands/ircusercommand.h"

#include "commands/irccommands.h"
#include "responses/ircresponsesfactory.h"

namespace ircserv
{

IRCUserCommand::IRCUserCommand() : IRCCommand(Enum_IRCCommands_User)
{
    Initialize();
}

void IRCUserCommand::Initialize(void)
{
}

IRCUserCommand::~IRCUserCommand()
{
    Shutdown();
}

void IRCUserCommand::Shutdown(void)
{
}

bool IRCUserCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCUserCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.empty())
    {

        return false;
    }
    return true;
}

}
