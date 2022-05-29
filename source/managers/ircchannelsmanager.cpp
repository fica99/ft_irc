#include "main/precomp.h"

#include "managers/ircchannelsmanager.h"

#include "ircclient/ircclient.h"
#include "managers/ircclientsmanager.h"
#include "utils/memory.h"

#define MAX_NB_USERS_IN_CHANNEL 40
#define MAX_NB_JOINED_CHANNELS 10

namespace ircserv
{

IMPLEMENT_SIMPLE_SINGLETON(IRCChannelsManager);

IRCChannelsManager::IRCChannelsManager()
{
    IMPLEMENT_SIMPLE_SINGLETON_CONSTRUCTOR();

    Initialize();
}

void IRCChannelsManager::Initialize(void)
{
}

IRCChannelsManager::~IRCChannelsManager()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void IRCChannelsManager::Shutdown(void)
{
    for (std::unordered_map<std::string, IRCChannel*>::iterator it = m_ChannelsMap.begin(); it != m_ChannelsMap.end(); )
    {
        Delete(it->second);
        it = m_ChannelsMap.erase(it);
    }
    m_ChannelsMap.clear();
}

Enum_IRCResponses IRCChannelsManager::Join(IRCSocket *socket, const std::string& channelName, const std::string& key)
{
    IRCChannel *channel = FindChannel(channelName);

    if (channel == NULL)
    {
        IRCClient *client = GetIRCClientsManager().FindClient(socket);
        if (client == NULL)
        {
            return Enum_IRCResponses_Unknown;
        }

        if (client->GetNumberJoinedChannels() >= MAX_NB_JOINED_CHANNELS)
        {
            return Enum_IRCResponses_ERR_TOOMANYCHANNELS;
        }

        channel = CreateChannel(channelName);
        if (channel == NULL)
        {
            return Enum_IRCResponses_Unknown;
        }

        channel->SetKey(key);
        channel->SetOperator(socket);
    }

    if (channel->GetUsers().size() >= MAX_NB_USERS_IN_CHANNEL)
    {
        return Enum_IRCResponses_ERR_CHANNELISFULL;
    }

    if (channel->GetIsInviteOnly())
    {
        return Enum_IRCResponses_ERR_INVITEONLYCHAN;
    }
    
    if (channel->GetKey() != key)
    {
        return Enum_IRCResponses_ERR_BADCHANNELKEY;
    }

    if (channel->AddUser(socket) == false)
    {
        return Enum_IRCResponses_Unknown;
    }
    // add check mask
    return Enum_IRCResponses_RPL_TOPIC;
}

Enum_IRCResponses IRCChannelsManager::Part(IRCSocket *socket, const std::string& channelName)
{
    if (IsInChannel(channelName, socket))
    {
        return Enum_IRCResponses_ERR_NOTONCHANNEL;
    }
    IRCChannel *channel = FindChannel(channelName);
    if (channel)
    {
        channel->RemoveUser(socket);
        if (channel->GetUsers().empty())
        {
            RemoveChannel(channelName);
        }
    }
    return Enum_IRCResponses_Unknown;
}


IRCChannel* IRCChannelsManager::FindChannel(const std::string& channelName) const
{
    IRCChannel *channel;

    std::unordered_map<std::string, IRCChannel*>::const_iterator it = m_ChannelsMap.find(channelName);
    if (it == m_ChannelsMap.end())
    {
        channel = NULL;
    }
    else
    {
        channel = it->second;
    }
    return channel;
}

IRCChannel* IRCChannelsManager::CreateChannel(const std::string& channelName)
{
    IRCChannel *channel;

    channel = New(IRCChannel);
    if (channel != NULL)
    {
        channel->SetName(channelName);
        m_ChannelsMap[channelName] = channel;
        IRC_LOGI("%s channel created", channelName.c_str());
    }
    return channel;
}

void IRCChannelsManager::RemoveChannel(const std::string channelName)
{
    IRCChannel *channel = FindChannel(channelName);
    if (channel)
    {
        Delete(channel);
        m_ChannelsMap.erase(m_ChannelsMap.find(channelName));
        IRC_LOGI("%s channel removed", channelName.c_str());
    }
}

IRCChannel* IRCChannelsManager::FindOrCreateChannel(const std::string& channelName)
{
    IRCChannel *channel = FindChannel(channelName);
    if (channel == NULL)
    {
        channel = CreateChannel(channelName);
    }
    return channel;
}

bool IRCChannelsManager::IsInChannel(const std::string& channelName, IRCSocket *socket) const
{
    IRCChannel *channel = FindChannel(channelName);
    if (channel == NULL)
    {
        return false;
    }
    return channel->GetUsers().find(socket) != channel->GetUsers().end();
}



}
