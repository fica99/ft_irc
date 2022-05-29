#include "main/precomp.h"

#include "managers/ircchannelsmanager.h"

#include "ircclient/ircclient.h"
#include "utils/memory.h"

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
        RemoveChannel(it->first);
    }
    m_ChannelsMap.clear();
}

// Enum_IRCResponses IRCChannelsManager::Join(IRCSocket *socket, const std::string& channelName, const std::string& key)
// {

// }

// Enum_IRCResponses IRCChannelsManager::Part(IRCSocket *socket, const std::string& channelName)
// {
//     if (IsInChannel(channelName, socket))
//     {
//         return Enum_IRCResponses_ERR_NOTONCHANNEL;
//     }
//     IRCChannel *channel = FindChannel(channelName);
//     if (channel)
//     {
//         channel->RemoveUser(socket);
//         if (channel->GetUsers().empty())
//         {
//             RemoveChannel(channelName);
//         }
//     }
//     return Enum_IRCResponses_Unknown;
// }

// Enum_IRCResponses IRCChannelsManager::Topic(IRCSocket *socket, const std::string& channelName, const std::string& topic)
// {
//     if (IsInChannel(channelName, socket))
//     {
//         return Enum_IRCResponses_ERR_NOTONCHANNEL;
//     }
//     IRCChannel *channel = FindChannel(channelName);
//     if (channel)
//     {
//         channel->SetTopic(topic);
//         return Enum_IRCResponses_RPL_TOPIC;
//     }
//     return Enum_IRCResponses_Unknown;
// }

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


IRCChannel* IRCChannelsManager::FindOrCreateChannel(const std::string& channelName)
{
    IRCChannel *channel = FindChannel(channelName);
    if (channel == NULL)
    {
        channel = New(IRCChannel);
        if (channel != NULL)
        {
            channel->SetName(channelName);
            m_ChannelsMap[channelName] = channel;
            IRC_LOGI("%s channel created", channelName.c_str());
        }
    }
    return channel;
}


void IRCChannelsManager::RemoveChannel(const std::string& channelName)
{
    IRCChannel *channel = FindChannel(channelName);
    if (channel)
    {
        for (std::unordered_set<IRCClient*>::iterator it = channel->GetClients().begin(); it != channel->GetClients().end(); ++it)
        {
            IRCClient *client = *it;
            if (client)
            {
                client->LeaveChannel(channel);
                channel->RemoveClient(client);
                channel->RemoveOper(client);
            }
        }
        Delete(channel);
        m_ChannelsMap.erase(m_ChannelsMap.find(channelName));
        IRC_LOGI("%s channel removed", channelName.c_str());
    }
}

std::vector<std::string> IRCChannelsManager::GetChannelsNames(void) const
{
    std::vector<std::string> channels;

    for (std::unordered_map<std::string, IRCChannel*>::const_iterator it = m_ChannelsMap.begin(); it != m_ChannelsMap.end(); ++it)
    {
        channels.push_back(it->first);
    }
    return channels;
}


}
