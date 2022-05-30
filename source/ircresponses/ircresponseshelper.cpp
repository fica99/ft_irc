#include "main/precomp.h"

#include "ircresponses/ircresponseshelper.h"

#include "ircclient/ircclient.h"
#include "ircchannel/ircchannel.h"
#include "ircresponses/ircresponserpl_namreply.h"
#include "ircresponses/ircresponsesfactory.h"
#include "ircserver/ircserver.h"
#include "managers/ircclientsmanager.h"
#include "managers/ircchannelsmanager.h"

namespace ircserv
{

void IRCResponsesHelper::Send(IRCSocket *socket, const std::string& message)
{
    if (socket)
    {
        socket->Send(message);
        IRC_LOGD("Sent message: %s", message.c_str());
    }
}

void IRCResponsesHelper::SendResponse(IRCSocket *socket, IRCResponse *response)
{
    if (response != NULL)
    {
        IRCClient* client = GetIRCClientsManager().FindClient(socket);
        response->SetNickname(client ? client->GetNickname() : "");
        response->SetPrefix(GetIRCServer().GetServerName());
        Send(socket, response->GetResponse());
    }
}

void IRCResponsesHelper::SendResponseWithParams(IRCSocket *socket, Enum_IRCResponses responseEnum, const std::string& arg1, const std::string& arg2)
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
            IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_RPL_MOTD, line);
        }
    }
    else
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOMOTD);
    }
}

void IRCResponsesHelper::SendMOTD(IRCSocket *socket, const std::string& server, const std::string& filename)
{
    SendResponseWithParams(socket, Enum_IRCResponses_RPL_MOTDSTART, server);
    SendRPL_MOTD(socket, filename);
    SendResponseWithParams(socket, Enum_IRCResponses_RPL_ENDOFMOTD);
}

void IRCResponsesHelper::SendTopic(IRCSocket *socket, const std::string& channel, const std::string& topic)
{
    if (topic.empty())
    {
        SendResponseWithParams(socket, Enum_IRCResponses_RPL_NOTOPIC, channel);
    }
    else
    {
        SendResponseWithParams(socket, Enum_IRCResponses_RPL_TOPIC, channel, topic);
    }
}

void IRCResponsesHelper::SendChannelNames(IRCSocket *socket, const std::string& channelName)
{
    IRCChannel *channel = GetIRCChannelsManager().FindChannel(channelName);
    if (channel)
    {
        IRCResponseRPL_NAMREPLY* response = dynamic_cast<IRCResponseRPL_NAMREPLY*>(IRCResponsesFactory::CreateResponse(Enum_IRCResponses_RPL_NAMREPLY));

        if (response != NULL)
        {
            response->SetChannel(channelName);
            for (std::unordered_set<IRCClient*>::iterator it = channel->GetClients().begin(); it != channel->GetClients().end(); ++it)
            {
                response->AddNick(channel->GetOpers().find(*it) != channel->GetOpers().end(), (*it)->GetNickname());
            }
            SendResponse(socket, response);
        }

        IRCResponsesFactory::DestroyResponse(response);
    }
}

}
