#include "main/precomp.h"

#include "irccommands/ircusercommand.h"

#include "irccommands/irccommands.h"
#include "ircresponses/ircresponseshelper.h"
#include "ircresponses/ircresponses.h"
#include "ircserver/ircserver.h"
#include "ircserver/ircsocket.h"
#include "managers/ircclientsmanager.h"
#include "managers/irccommandsmanager.h"

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
        IRCClient *client = GetIRCClientsManager().FindOrCreateClient(socket);
        if (client->GetIsRegistered())
        {
            IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_ALREADYREGISTRED);
            return false;
        }
        client->SetUsername(GetUsername());
        client->SetRealname(GetRealname());
        if (client->GetIsRegistered() == true)
        {
//            if (client->GetPassword() != GetIRCServer().GetPassword())
//            {
//                GetIRCCommandsManager().ProcessCommands("QUIT\n\r", socket);
//            }
//            else
//            {
                IRCResponsesHelper::SendMOTD(socket, GetIRCServer().GetServerName(), "./conf/IRC.motd");
                return true;
            //}
        }
    }
    return false;
}

bool IRCUserCommand::ValidateArgs(IRCSocket *socket)
{
    if (GetArgs().size() < 4)
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NEEDMOREPARAMS, EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
        return false;
    }
    else
    {
        SetUsername(GetArgs()[0]);
        SetRealname(GetArgs()[3]);
    }
    return true;
}

}
