#pragma once

#include <string>
#include <unordered_map>

#include "ircchannel/ircchannel.h"
// #include "ircserver/ircsocket.h"
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
    IRCChannel* FindChannel(const std::string& channelName) const;
    IRCChannel* FindOrCreateChannel(const std::string& channelName);
    void RemoveChannel(const std::string& channelName);

    // bool IsInChannel(const std::string& channelName, IRCSocket *socket) const;
private:
    std::unordered_map<std::string, IRCChannel*> m_ChannelsMap;
};

#define GetIRCChannelsManager() IRCChannelsManager::GetInstance()

}
