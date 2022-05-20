#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseRPL_TOPIC : public IRCResponse
{
public:
    IRCResponseRPL_TOPIC();
    virtual ~IRCResponseRPL_TOPIC();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetChannel(const std::string& channel) { m_Channel = channel; }
    inline void SetTopic(const std::string& topic) { m_Topic = topic; }

private:
    std::string m_Channel;
    std::string m_Topic;
};

}
