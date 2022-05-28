#include "main/precomp.h"

#include "managers/ircchannelsmanager.h"

#include "utils/memory.h"

#define MAX_NB_USERS_IN_CHANNEL 40

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
    if (channel != NULL)
    {
        if (channel->GetUsers().size() >= MAX_NB_USERS_IN_CHANNEL)
        {
            return Enum_IRCResponses_ERR_CHANNELISFULL;
        }
    }
    else
    {
        channel = CreateChannel(channelName);
        if (channel != NULL)
        {
            channel->SetKey(key);
            channel->SetOperator(socket);
        }
    }
    
    channel->AddUser(socket);

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

IRCChannel* IRCChannelsManager::FindOrCreateChannel(const std::string& channelName)
{
    IRCChannel *channel = FindChannel(channelName);
    if (channel == NULL)
    {
        channel = CreateChannel(channelName);
    }
    return channel;
}


}
