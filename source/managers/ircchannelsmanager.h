#pragma once

#include <string>
#include <unordered_map>

#include "ircchannel/ircchannel.h"
#include "ircresponses/ircresponses.h"
#include "ircserver/ircsocket.h"
#include "utils/singleton.h"

namespace ircserv
{

class IRCChannelsManager
{
public:
    IRCChannelsManager();
    virtual ~IRCChannelsManager();
    DECLARE_SIMPLE_SINGLETON(IRCChannelsManager);

private:
    void Initialize(void);
    void Shutdown(void);

public:
    Enum_IRCResponses Join(IRCSocket *socket, const std::string& channelName, const std::string& key);

public:
    IRCChannel* FindChannel(const std::string& channelName) const;
    IRCChannel* CreateChannel(const std::string& channelName);
    IRCChannel* FindOrCreateChannel(const std::string& channelName);
private:
    std::unordered_map<std::string, IRCChannel*> m_ChannelsMap;
};

#define GetIRCChannelsManager() IRCChannelsManager::GetInstance()

}
