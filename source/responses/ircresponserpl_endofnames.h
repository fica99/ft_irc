#pragma once

#include <string>

#include "responses/ircresponse.h"

namespace ircserv
{

class IRCResponseRPL_ENDOFNAMES : public IRCResponse
{
public:
    IRCResponseRPL_ENDOFNAMES();
    virtual ~IRCResponseRPL_ENDOFNAMES();
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
