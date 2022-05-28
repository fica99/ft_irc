#include "main/precomp.h"

#include "irccommands/ircusercommand.h"

#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
#include "ircresponses/ircresponses.h"
#include "ircserver/ircserver.h"
#include "ircserver/ircsocket.h"
#include "managers/ircclientsmanager.h"
#include "parsing/ircparsinghelper.h"

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

bool IRCUserCommand::ProcessCommand(IRCSocket *socket)
{
    if (ValidateArgs(socket))
    {
        Enum_IRCResponses responseEnum = GetIRCClientsManager().User(socket, GetUsername(), GetRealname());
       if (responseEnum == Enum_IRCResponses_ERR_ALREADYREGISTRED)
        {
            IRCCommandsHelper::SendResponseWithoutParams(socket, Enum_IRCResponses_ERR_ALREADYREGISTRED);
            return false;
        }
        else if (responseEnum == Enum_IRCResponses_RPL_MOTD)
        {
            IRCCommandsHelper::SendMOTD(socket, "IRC", "./conf/IRC.motd");
        }
        return true;
    }
    return false;
}

bool IRCUserCommand::ValidateArgs(IRCSocket *socket)
{
    if (GetArgs().size() < 4)
    {
        IRCCommandsHelper::SendERR_NEEDMOREPARAMS(socket, GetCommandEnum());
        return false;
    }
    else
    {
        if (!IRCParsingHelper::IsUser(GetArgs()[0]))
        {
            return false;
        }
        SetUsername(GetArgs()[0]);
        SetRealname(GetArgs()[3]);
    }
    return true;
}

}
