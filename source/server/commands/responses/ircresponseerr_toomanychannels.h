#pragma once

#include <string>

#include "server/commands/responses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_TOOMANYCHANNELS : public IRCResponse
{
public:
    IRCResponseERR_TOOMANYCHANNELS();
    virtual ~IRCResponseERR_TOOMANYCHANNELS();
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
