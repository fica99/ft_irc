#pragma once

#include <string>
#include <vector>
#include <utility>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseRPL_LIST : public IRCResponse
{
public:
    IRCResponseRPL_LIST();
    virtual ~IRCResponseRPL_LIST();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetChannel(const std::string& channel) { m_Channel = channel; }
    inline void SetNbVisible(const std::string nbVisible) { m_NbVisible = nbVisible; }
    inline void SetTopic(const std::string& topic) { m_Topic = topic; }

private:
    std::string m_Channel;
    std::string m_NbVisible;
    std::string m_Topic;
};

}
