#include "main/precomp.h"

#include "irccommands/ircpasscommand.h"

#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
#include "ircresponses/ircresponses.h"
#include "ircserver/ircsocket.h"
#include "managers/ircclientsmanager.h"

namespace ircserv
{

IRCPassCommand::IRCPassCommand() : IRCCommand(Enum_IRCCommands_Pass)
{
    Initialize();
}

void IRCPassCommand::Initialize(void)
{
}

IRCPassCommand::~IRCPassCommand()
{
    Shutdown();
}

void IRCPassCommand::Shutdown(void)
{
}

bool IRCPassCommand::ProcessCommand(IRCSocket *socket)
{
    if (ValidateArgs(socket))
    {
        if (GetIRCClientsManager().Pass(socket, GetPassword()) == false)
        {
            IRCCommandsHelper::SendResponseWithoutParams(socket, Enum_IRCResponses_ERR_ALREADYREGISTRED);
            return false;
        }
        return true;
    }
    return false;
}

bool IRCPassCommand::ValidateArgs(IRCSocket *socket)
{
    if (GetArgs().empty())
    {
        IRCCommandsHelper::SendERR_NEEDMOREPARAMS(socket, GetCommandEnum());
        return false;
    }
    SetPassword(GetArgs()[0]);
    return true;
}

}
