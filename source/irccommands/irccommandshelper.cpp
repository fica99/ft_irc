#include "main/precomp.h"

#include "irccommands/irccommandshelper.h"

#include "ircclient/ircclient.h"
#include "ircserver/ircserver.h"
#include "ircresponses/ircresponsesfactory.h"
#include "managers/ircclientsmanager.h"

namespace ircserv
{

static void SendResponse(IRCSocket *socket, IRCResponse *response)
{
    if (response != NULL)
    {
        IRCClient* client = GetIRCClientsManager().FindClient(socket);
        response->SetNickname(client ? client->GetNickname() : "");
        response->SetPrefix(GetIRCServer().GetServerName());
        response->Send(socket);
    }
}

void IRCCommandsHelper::SendResponseWithParams(IRCSocket *socket, Enum_IRCResponses responseEnum, const std::string& arg1, const std::string& arg2)
{
    IRCResponse* response = IRCResponsesFactory::CreateResponse(responseEnum, arg1, arg2);

    if (response != NULL)
    {
        SendResponse(socket, response);
    }

    IRCResponsesFactory::DestroyResponse(response);
}


static void SendRPL_MOTD(IRCSocket *socket, const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;

    if (file.good())
    {
        while (std::getline(file, line))
        {
            IRCCommandsHelper::SendResponseWithParams(socket, Enum_IRCResponses_RPL_MOTD, line);
        }
    }
    else
    {
        IRCCommandsHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOMOTD);
    }
}

void IRCCommandsHelper::SendMOTD(IRCSocket *socket, const std::string& server, const std::string& filename)
{
    SendResponseWithParams(socket, Enum_IRCResponses_RPL_MOTDSTART, server);
    SendRPL_MOTD(socket, filename);
    SendResponseWithParams(socket, Enum_IRCResponses_RPL_ENDOFMOTD);
}

}
