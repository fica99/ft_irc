#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_NOTONCHANNEL : public IRCResponse
{
public:
    IRCResponseERR_NOTONCHANNEL();
    virtual ~IRCResponseERR_NOTONCHANNEL();
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
