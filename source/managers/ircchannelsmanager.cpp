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
        EraseChannel(it->first);
    }
    m_ChannelsMap.clear();
}

IRCChannel* IRCChannelsManager::CreateChannel(const std::string& channelName)
{
    IRCChannel* channel = New(IRCChannel);
    if (channel != NULL)
    {
        channel->SetName(channelName);
        m_ChannelsMap[channelName] = channel;
        IRC_LOGI("%s", "Channel created");
    }
    return channel;
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


IRCChannel* IRCChannelsManager::FindOrCreateChannel(const std::string& channelName)
{
    IRCChannel *channel = FindChannel(channelName);
    if (channel == NULL)
    {
        channel = CreateChannel(channelName);
    }
    return channel;
}

void IRCChannelsManager::EraseChannel(const std::string& channelName)
{
    std::unordered_map<std::string, IRCChannel*>::iterator it = m_ChannelsMap.find(channelName);
    if (it != m_ChannelsMap.end())
    {
        IRCChannel *channel = it->second;
        if (channel)
        {
            for (std::unordered_set<IRCClient*>::iterator it_client = channel->GetClients().begin(); it_client != channel->GetClients().end(); ++it_client)
            {
                IRCClient *client = *it_client;
                client->LeaveChannel(channel);
            }
            Delete(channel);
            m_ChannelsMap.erase(it);
            IRC_LOGI("%s", "Channel removed");
        }
    }
}

}
