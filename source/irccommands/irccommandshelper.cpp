#include "main/precomp.h"

#include "irccommands/irccommandshelper.h"

#include "ircclient/ircclient.h"
#include "ircresponses/ircresponse.h"
#include "ircresponses/ircresponseerr_badchannelkey.h"
#include "ircresponses/ircresponseerr_channelisfull.h"
#include "ircresponses/ircresponseerr_erroneusnickname.h"
#include "ircresponses/ircresponseerr_inviteonlychan.h"
#include "ircresponses/ircresponseerr_needmoreparams.h"
#include "ircresponses/ircresponseerr_nicknameinuse.h"
#include "ircresponses/ircresponseerr_nomotd.h"
#include "ircresponses/ircresponseerr_nosuchchannel.h"
#include "ircresponses/ircresponseerr_toomanychannels.h"
#include "ircresponses/ircresponseerr_unknowncommand.h"
#include "ircresponses/ircresponserpl_endofmotd.h"
#include "ircresponses/ircresponserpl_motd.h"
#include "ircresponses/ircresponserpl_motdstart.h"
#include "ircresponses/ircresponserpl_notopic.h"
#include "ircresponses/ircresponserpl_topic.h"
#include "ircresponses/ircresponses.h"
#include "ircresponses/ircresponsesfactory.h"
#include "managers/ircclientsmanager.h"

namespace ircserv
{

void IRCCommandsHelper::SendResponseWithoutParams(IRCSocket *socket, Enum_IRCResponses responseEnum)
{
    IRCResponse* response = IRCResponsesFactory::CreateResponse(responseEnum);
    if (response != NULL)
    {
        IRCClient* client = GetIRCClientsManager().FindClient(socket);
        response->SetNickname(client ? client->GetNickname() : "");
        response->Send(socket);
    }
    IRCResponsesFactory::DestroyResponse(response);
}

void IRCCommandsHelper::SendERR_NEEDMOREPARAMS(IRCSocket *socket, Enum_IRCCommands commandEnum)
{
    const std::string command = EnumString<Enum_IRCCommands>::From(commandEnum);
    IRCResponseERR_NEEDMOREPARAMS* response = dynamic_cast<IRCResponseERR_NEEDMOREPARAMS*>(
        IRCResponsesFactory::CreateResponse(Enum_IRCResponses_ERR_NEEDMOREPARAMS)
    );
    if (response != NULL)
    {
        IRCClient* client = GetIRCClientsManager().FindClient(socket);
        response->SetNickname(client ? client->GetNickname() : "");
        response->SetCommand(command);
        response->Send(socket);
    }
    IRCResponsesFactory::DestroyResponse(response);
}

void IRCCommandsHelper::SendERR_ERRONEUSNICKNAME(IRCSocket *socket, const std::string& nick)
{
    IRCResponseERR_ERRONEUSNICKNAME* response = dynamic_cast<IRCResponseERR_ERRONEUSNICKNAME*>(
        IRCResponsesFactory::CreateResponse(Enum_IRCResponses_ERR_ERRONEUSNICKNAME)
    );
    if (response != NULL)
    {
        IRCClient* client = GetIRCClientsManager().FindClient(socket);
        response->SetNickname(client ? client->GetNickname() : "");
        response->SetNick(nick);
        response->Send(socket);
    }
    IRCResponsesFactory::DestroyResponse(response);
}

void IRCCommandsHelper::SendERR_NICKNAMEINUSE(IRCSocket *socket, const std::string& nick)
{
    IRCResponseERR_NICKNAMEINUSE *response = dynamic_cast<IRCResponseERR_NICKNAMEINUSE*>(
        IRCResponsesFactory::CreateResponse(Enum_IRCResponses_ERR_NICKNAMEINUSE)
    );
    if (response != NULL)
    {
        IRCClient* client = GetIRCClientsManager().FindClient(socket);
        response->SetNickname(client ? client->GetNickname() : "");
        response->SetNick(nick);
        response->Send(socket);
    }
    IRCResponsesFactory::DestroyResponse(response);
}

void IRCCommandsHelper::SendRPL_MOTDSTART(IRCSocket *socket, const std::string server)
{
    IRCResponseRPL_MOTDSTART *response = dynamic_cast<IRCResponseRPL_MOTDSTART*>(
        IRCResponsesFactory::CreateResponse(Enum_IRCResponses_RPL_MOTDSTART)
    );
    if (response != NULL)
    {
        IRCClient* client = GetIRCClientsManager().FindClient(socket);
        response->SetNickname(client ? client->GetNickname() : "");
        response->SetServer(server);
        response->Send(socket);
    }
    IRCResponsesFactory::DestroyResponse(response);
}

void IRCCommandsHelper::SendRPL_MOTD(IRCSocket *socket, const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;

    if (file.good())
    {
        while (std::getline(file, line))
        {
            IRCResponseRPL_MOTD *response = dynamic_cast<IRCResponseRPL_MOTD*>(
                IRCResponsesFactory::CreateResponse(Enum_IRCResponses_RPL_MOTD)
            );
            if (response != NULL)
            {
                IRCClient* client = GetIRCClientsManager().FindClient(socket);
                response->SetNickname(client ? client->GetNickname() : "");
                response->SetText(line);
                response->Send(socket);
            }
            IRCResponsesFactory::DestroyResponse(response);
        }
    }
    else
    {
        SendResponseWithoutParams(socket, Enum_IRCResponses_ERR_NOMOTD);
    }
}


void IRCCommandsHelper::SendMOTD(IRCSocket *socket, const std::string server, const std::string& filename)
{
    IRCCommandsHelper::SendRPL_MOTDSTART(socket, server);
    IRCCommandsHelper::SendRPL_MOTD(socket, filename);
    SendResponseWithoutParams(socket, Enum_IRCResponses_RPL_ENDOFMOTD);
    IRC_LOGD("%s", "Client registered");
}

void IRCCommandsHelper::SendERR_UNKNOWNCOMMAND(IRCSocket *socket, const std::string& command)
{
    IRCResponseERR_UNKNOWNCOMMAND *response = dynamic_cast<IRCResponseERR_UNKNOWNCOMMAND*>(
        IRCResponsesFactory::CreateResponse(Enum_IRCResponses_ERR_UNKNOWNCOMMAND)
    );
    if (response != NULL)
    {
        IRCClient* client = GetIRCClientsManager().FindClient(socket);
        response->SetNickname(client ? client->GetNickname() : "");
        response->SetCommand(command);
        response->Send(socket);
    }
    IRCResponsesFactory::DestroyResponse(response);
}

void IRCCommandsHelper::SendResponseWithServerName(IRCSocket *socket, Enum_IRCResponses responseEnum, const std::string& channelName)
{
    IRCResponse *response = IRCResponsesFactory::CreateResponse(responseEnum);
    if (response != NULL)
    {
        IRCClient* client = GetIRCClientsManager().FindClient(socket);
        response->SetNickname(client ? client->GetNickname() : "");
        if (responseEnum == Enum_IRCResponses_ERR_NOSUCHCHANNEL)
        {
            dynamic_cast<IRCResponseERR_NOSUCHCHANNEL*>(response)->SetChannelName(channelName);
        }
        else if (responseEnum == Enum_IRCResponses_ERR_INVITEONLYCHAN)
        {
            dynamic_cast<IRCResponseERR_INVITEONLYCHAN*>(response)->SetChannel(channelName);
        }
        else if (responseEnum == Enum_IRCResponses_ERR_CHANNELISFULL)
        {
            dynamic_cast<IRCResponseERR_CHANNELISFULL*>(response)->SetChannel(channelName);
        }
        else if (responseEnum == Enum_IRCResponses_ERR_TOOMANYCHANNELS)
        {
            dynamic_cast<IRCResponseERR_TOOMANYCHANNELS*>(response)->SetChannelName(channelName);
        }
        else if (responseEnum == Enum_IRCResponses_ERR_BADCHANNELKEY)
        {
            dynamic_cast<IRCResponseERR_BADCHANNELKEY*>(response)->SetChannel(channelName);
        }
        response->Send(socket);
    }
    IRCResponsesFactory::DestroyResponse(response);
}

void IRCCommandsHelper::SendResponseWithTopic(IRCSocket *socket, const std::string& channelName, const std::string& topic)
{
    IRCResponse *response = NULL;

    if (topic.empty())
    {
        IRCResponseRPL_NOTOPIC *responseNoTopic = dynamic_cast<IRCResponseRPL_NOTOPIC*>(IRCResponsesFactory::CreateResponse(Enum_IRCResponses_RPL_NOTOPIC));
        if (responseNoTopic != NULL)
        {
            responseNoTopic->SetChannel(channelName);
            response = responseNoTopic;
        }
    }
    else
    {
        IRCResponseRPL_TOPIC *responseTopic = dynamic_cast<IRCResponseRPL_TOPIC*>(IRCResponsesFactory::CreateResponse(Enum_IRCResponses_RPL_TOPIC));
        if (responseTopic != NULL)
        {
            responseTopic->SetTopic(topic);
            responseTopic->SetChannel(channelName);
            response = responseTopic;
        }
    }
    if (response != NULL)
    {
        IRCClient* client = GetIRCClientsManager().FindClient(socket);
        response->SetNickname(client ? client->GetNickname() : "");
        response->Send(socket);
    }
    IRCResponsesFactory::DestroyResponse(response);
}

}
