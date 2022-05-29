#include "main/precomp.h"

#include "irccommands/ircnickcommand.h"

#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
#include "ircresponses/ircresponses.h"
#include "ircserver/ircserver.h"
#include "ircserver/ircsocket.h"
#include "managers/ircclientsmanager.h"
#include "managers/irccommandsmanager.h"
#include "parsing/ircparsinghelper.h"

namespace ircserv
{

IRCNickCommand::IRCNickCommand() : IRCCommand(Enum_IRCCommands_Nick)
{
    Initialize();
}

void IRCNickCommand::Initialize(void)
{
}

IRCNickCommand::~IRCNickCommand()
{
    Shutdown();
}

void IRCNickCommand::Shutdown(void)
{
}

bool IRCNickCommand::ProcessCommand(IRCSocket* socket)
{
    if (ValidateArgs(socket))
    {
        if (GetIRCClientsManager().FindClientByNickname(GetNickname()) != NULL)
        {
            IRCCommandsHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NICKNAMEINUSE);
            return false;
        }
        IRCClient *client = GetIRCClientsManager().FindOrCreateClient(socket);
        bool wasRegistered = client->GetIsRegistered();
        client->SetNickname(GetNickname());
        if (client->GetIsRegistered() == true)
        {
            if (client->GetPassword() != GetIRCServer().GetPassword())
            {
                GetIRCCommandsManager().ProcessCommands("QUIT\n\r", socket);
            }
            else if (wasRegistered == false)
            {
                IRCCommandsHelper::SendMOTD(socket, GetIRCServer().GetServerName(), "./conf/IRC.motd");
                return true;
            }
        }
    }
    return false;
}

bool IRCNickCommand::ValidateArgs(IRCSocket* socket)
{
    if (GetArgs().empty())
    {
        IRCCommandsHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NONICKNAMEGIVEN);
        return false;
    }
    else
    {
        if (!IRCParsingHelper::IsNick(GetArgs()[0]))
        {
            IRCCommandsHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_ERRONEUSNICKNAME, GetArgs()[0]);
            return false;
        }
        SetNickname(GetArgs()[0]);
    }
    return true;
}


}
