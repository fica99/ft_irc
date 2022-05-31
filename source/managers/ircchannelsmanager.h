#pragma once

#include <string>
#include <unordered_map>

#include "ircchannel/ircchannel.h"
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
    IRCChannel* CreateChannel(const std::string& channelName);
    IRCChannel* FindChannel(const std::string& channelName) const;
    IRCChannel* FindOrCreateChannel(const std::string& channelName);
    void EraseChannel(const std::string& channelName);

public:
    inline const std::unordered_map<std::string, IRCChannel*>& GetChannelsMap(void) const { return m_ChannelsMap; }

private:
    std::unordered_map<std::string, IRCChannel*> m_ChannelsMap;
};

#define GetIRCChannelsManager() IRCChannelsManager::GetInstance()

}
