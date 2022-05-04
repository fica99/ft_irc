#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_CHANNELISFULL : public IRCResponse
{
public:
    IRCResponseERR_CHANNELISFULL();
    virtual ~IRCResponseERR_CHANNELISFULL();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetChannel(const std::string& channel) { m_Channel = channel; }

private:
    std::string m_Channel;
};

}
