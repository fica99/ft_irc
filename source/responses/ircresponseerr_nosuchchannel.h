#pragma once

#include <string>

#include "responses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_NOSUCHCHANNEL : public IRCResponse
{
public:
    IRCResponseERR_NOSUCHCHANNEL();
    virtual ~IRCResponseERR_NOSUCHCHANNEL();
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
