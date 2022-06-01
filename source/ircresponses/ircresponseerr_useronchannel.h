#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_USERONCHANNEL : public IRCResponse
{
public:
    IRCResponseERR_USERONCHANNEL();
    virtual ~IRCResponseERR_USERONCHANNEL();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetUser(const std::string& user) { m_User = user; }
    inline const std::string& GetUser(void) const { return m_User; }
    inline void SetChannel(const std::string& channel) { m_Channel = channel; }
    inline const std::string& GetChannel(void) const { return m_Channel; }

private:
    std::string m_User;
    std::string m_Channel;
};

}
