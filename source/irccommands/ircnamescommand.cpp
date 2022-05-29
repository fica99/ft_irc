#include "main/precomp.h"

#include "irccommands/ircnamescommand.h"

#include "ircclient/ircclient.h"
#include "ircchannel/ircchannel.h"
#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
#include "parsing/ircparsinghelper.h"
#include "ircresponses/ircresponserpl_namreply.h"
#include "ircresponses/ircresponsesfactory.h"
#include "managers/ircchannelsmanager.h"
#include "managers/ircclientsmanager.h"

namespace ircserv
{

IRCNamesCommand::IRCNamesCommand() : IRCCommand(Enum_IRCCommands_Names)
{
    Initialize();
}

void IRCNamesCommand::Initialize(void)
{
}

IRCNamesCommand::~IRCNamesCommand()
{
    Shutdown();
}

void IRCNamesCommand::Shutdown(void)
{
}
 

bool IRCNamesCommand::ProcessCommand(IRCSocket *socket)
{
    if (!GetIRCClientsManager().IsRegistered(socket))
    {
        IRCCommandsHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOTREGISTERED);
        return false;
    }

    if (ValidateArgs(socket))
    {
        if (GetChannels().empty())
        {
            std::vector<std::string> channelsNames = GetIRCChannelsManager().GetChannelsNames();
            for (size_t i = 0; i < channelsNames.size(); ++i)
            {
                SendChannelNames(socket, channelsNames[i]);
            }
            SendClientsWithNoChannels(socket);
            IRCCommandsHelper::SendResponseWithParams(socket, Enum_IRCResponses_RPL_ENDOFNAMES, "*");
        }
        else
        {
            for (size_t i = 0; i < GetChannels().size(); ++i)
            {
                IRCCommandsHelper::SendChannelNames(socket, GetChannels()[i]);
                IRCCommandsHelper::SendResponseWithParams(socket, Enum_IRCResponses_RPL_ENDOFNAMES, GetChannels()[i]);
            }
        }
        return true;
    }
    return false;
}

bool IRCNamesCommand::ValidateArgs(IRCSocket *socket)
{
    if (!GetArgs().empty())
    {
        SetChannels(IRCParsingHelper::Split(GetArgs()[0], ","));
    }
    return true;
}

void IRCNamesCommand::SendChannelNames(IRCSocket *socket, const std::string& channelName)
{
    IRCChannel *channel = GetIRCChannelsManager().FindChannel(channelName);
    if (channel)
    {
        if (channel->GetModes() & PRIVATE || channel->GetModes() & SECRET)
        {
            IRCClient *client = GetIRCClientsManager().FindClient(socket);
            if (client)
            {
                if (channel->GetClients().find(client) != channel->GetClients().end())
                {
                    IRCCommandsHelper::SendChannelNames(socket, channelName);
                }
            }
        }
        else
        {
            IRCCommandsHelper::SendChannelNames(socket, channelName);
        }
    }
}

void IRCNamesCommand::SendClientsWithNoChannels(IRCSocket *socket)
{
    std::vector<IRCClient*> clients = GetIRCClientsManager().GetAllClients();
    IRCResponseRPL_NAMREPLY* response = dynamic_cast<IRCResponseRPL_NAMREPLY*>(IRCResponsesFactory::CreateResponse(Enum_IRCResponses_RPL_NAMREPLY));

    if (response != NULL)
    {
        response->SetChannel("* *");
    }
    for (size_t i = 0; i < clients.size(); ++i)
    {
        if (clients[i]->GetJoinedChannels().empty() && clients[i]->GetIsRegistered())
        {
            if (response != NULL)
            {
                response->AddNick(false, clients[i]->GetNickname());
            }
        }
    }
    IRCCommandsHelper::SendResponse(socket, response);
    IRCResponsesFactory::DestroyResponse(response);
}


}
