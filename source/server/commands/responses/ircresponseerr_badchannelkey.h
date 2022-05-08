#pragma once

#include <string>

#include "server/commands/responses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_BADCHANNELKEY : public IRCResponse
{
public:
    IRCResponseERR_BADCHANNELKEY();
    virtual ~IRCResponseERR_BADCHANNELKEY();
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
