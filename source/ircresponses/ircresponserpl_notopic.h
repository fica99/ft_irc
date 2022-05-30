#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseRPL_NOTOPIC : public IRCResponse
{
public:
    IRCResponseRPL_NOTOPIC();
    virtual ~IRCResponseRPL_NOTOPIC();
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
