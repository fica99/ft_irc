#include "main/precomp.h"

#include "irccommands/ircnamescommand.h"

#include "ircclient/ircclient.h"
#include "ircchannel/ircchannel.h"
#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
#include "ircresponses/ircresponseshelper.h"
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
    if (!IRCCommandsHelper::IsRegistered(socket))
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOTREGISTERED);
        return false;
    }

    if (ValidateArgs(socket))
    {
        if (GetChannels().empty())
        {
            const std::unordered_map<std::string, IRCChannel*>& channelMap = GetIRCChannelsManager().GetChannelsMap();
            for (std::unordered_map<std::string, IRCChannel*>::const_iterator it = channelMap.begin(); it != channelMap.end(); ++it)
            {
                SendChannelNames(socket, it->first);
            }
            SendClientsWithNoChannels(socket);
            IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_RPL_ENDOFNAMES, "*");
        }
        else
        {
            for (size_t i = 0; i < GetChannels().size(); ++i)
            {
                SendChannelNames(socket, GetChannels()[i]);
                IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_RPL_ENDOFNAMES, GetChannels()[i]);
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

void IRCNamesCommand::SendChannelNames(IRCSocket *socket, const std::string& channelName) const
{
    IRCChannel *channel = GetIRCChannelsManager().FindChannel(channelName);
    if (channel)
    {
        if (channel->GetModes() & PRIVATE || channel->GetModes() & SECRET)
        {
            IRCClient *client = GetIRCClientsManager().FindClient(socket);
            if (!IRCCommandsHelper::IsInContainer(channel->GetClients(), client))
            {
                return;
            }
        }
        IRCResponsesHelper::SendChannelNames(socket, channelName);
    }
}

void IRCNamesCommand::SendClientsWithNoChannels(IRCSocket *socket) const
{
    IRCResponseRPL_NAMREPLY* response = dynamic_cast<IRCResponseRPL_NAMREPLY*>(IRCResponsesFactory::CreateResponse(Enum_IRCResponses_RPL_NAMREPLY));

    if (response != NULL)
    {
        response->SetChannel("* *");
    }
    const std::unordered_map<IRCSocket*, IRCClient*> socketsClientsMap = GetIRCClientsManager().GetSocketsClientsMap();
    for (std::unordered_map<IRCSocket*, IRCClient*>::const_iterator it = socketsClientsMap.begin(); it != socketsClientsMap.end(); ++it)
    {
        IRCClient *client = it->second;
        if (client && client->GetIsRegistered())
        {
            if (client->GetJoinedChannels().empty())
            {
                if (response != NULL)
                {
                    if (!(client->GetModes() & INVISIBLE))
                    {
                        response->AddNick(false, client->GetNickname());
                    }
                }
            }
        }
    }
    IRCResponsesHelper::SendResponse(socket, response);
    IRCResponsesFactory::DestroyResponse(response);
}


}
