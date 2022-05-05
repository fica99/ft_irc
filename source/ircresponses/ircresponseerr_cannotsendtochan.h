#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_CANNOTSENDTOCHAN : public IRCResponse
{
public:
    IRCResponseERR_CANNOTSENDTOCHAN();
    virtual ~IRCResponseERR_CANNOTSENDTOCHAN();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetChannelName(const std::string& channelName) { m_ChannelName = channelName; }

private:
    std::string m_ChannelName;
};

}
