#pragma once

#include <string>
#include <vector>
#include <utility>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseRPL_NAMREPLY : public IRCResponse
{
public:
    IRCResponseRPL_NAMREPLY();
    virtual ~IRCResponseRPL_NAMREPLY();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetChannel(const std::string& channel) { m_Channel = channel; }
    inline void AddNick(bool isOper, const std::string& nick) { m_Nicks.push_back(std::make_pair(isOper, nick)); }

private:
    std::string m_Channel;
    std::vector<std::pair<bool, std::string> > m_Nicks;
};

}
