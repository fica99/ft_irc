#include "main/precomp.h"

#include "irccommands/ircjoincommand.h"

#include "ircchannel/ircchannel.h"
#include "ircclient/ircclient.h"
#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
#include "ircresponses/ircresponseshelper.h"
#include "ircresponses/ircresponses.h"
#include "ircserver/ircsocket.h"
#include "managers/ircchannelsmanager.h"
#include "managers/ircclientsmanager.h"
#include "parsing/ircparsinghelper.h"

#define MAX_NB_USERS_IN_CHANNEL 40
#define MAX_NB_JOINED_CHANNELS 10

namespace ircserv
{

IRCJoinCommand::IRCJoinCommand() : IRCCommand(Enum_IRCCommands_Join)
{
    Initialize();
}

void IRCJoinCommand::Initialize(void)
{
}

IRCJoinCommand::~IRCJoinCommand()
{
    Shutdown();
}

void IRCJoinCommand::Shutdown(void)
{
}

bool IRCJoinCommand::ProcessCommand(IRCSocket *socket)
{
    if (!IRCCommandsHelper::IsRegistered(socket))
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOTREGISTERED);
        return false;
    }

    if (ValidateArgs(socket))
    {
        for (size_t i = 0; i < GetChannels().size(); ++i)
        {
            const std::string& channelName = GetChannels()[i];
            const std::string key = (i < GetKeys().size()) ? GetKeys()[i] : "";
            ProcessJoiningChannel(socket, channelName, key);
        }
        return true;
    }
    return false;
}

bool IRCJoinCommand::ValidateArgs(IRCSocket *socket)
{
    if (GetArgs().empty())
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NEEDMOREPARAMS, EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
        return false;
    }
    else
    {
        std::vector<std::string> channels;
        std::vector<std::string> keys;

        channels = IRCParsingHelper::Split(GetArgs()[0], ",");
        if (GetArgs().size() > 1)
        {
            keys = IRCParsingHelper::Split(GetArgs()[1], ",");
        }

        for (size_t i = 0; i < channels.size(); )
        {
            if (!IRCParsingHelper::IsChannel(channels[i]))
            {
                IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOSUCHCHANNEL, channels[i]);
                if (i < keys.size())
                {
                    keys.erase(keys.begin() + i);
                }
                channels.erase(channels.begin() + i);
            }
            else
            {
                ++i;
            }
        }
        SetChannels(channels);
        SetKeys(keys);
    }
    return true;
}

void IRCJoinCommand::ProcessJoiningChannel(IRCSocket *socket, const std::string& channelName, const std::string& key) const
{
    IRCClient *client = GetIRCClientsManager().FindClient(socket);

    if (client != NULL)
    {
        if (client->GetJoinedChannels().size() >= MAX_NB_JOINED_CHANNELS)
        {
            IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_TOOMANYCHANNELS, channelName);
            return;
        }
    }

    IRCChannel *channel = GetIRCChannelsManager().FindChannel(channelName);

    if (channel == NULL)
    {
        channel = GetIRCChannelsManager().FindOrCreateChannel(channelName);
        if (channel != NULL)
        {
            channel->AddOper(client);
            channel->SetKey(key);
        }
    }

    if (channel->GetClients().size() >= MAX_NB_USERS_IN_CHANNEL)
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_CHANNELISFULL, channelName);
        return;
    }

    if (channel->GetModes() & INVITEONLY)
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_INVITEONLYCHAN, channelName);
        return;
    }

    if (channel->GetKey() != key)
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_BADCHANNELKEY, channelName);
        return;
    }
    
    if (IRCCommandsHelper::IsBannedByChannel(client, channel))
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_BANNEDFROMCHAN, channelName);
        return;
    }

    channel->AddClient(client);

    std::string message = ":" + client->GetNickname() + "!" + client->GetUsername() + "@" + client->GetHostname() + " " + EnumString<Enum_IRCCommands>::From(GetCommandEnum()) + " :" + channelName + "\n";
    IRCResponsesHelper::SendMessageToAllChannelNames(channelName, message);
    IRCResponsesHelper::SendTopic(socket, channelName, channel->GetTopic());
    IRCResponsesHelper::SendChannelNames(socket, channelName);
}


}
