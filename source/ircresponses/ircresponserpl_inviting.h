#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseRPL_INVITING : public IRCResponse
{
public:
    IRCResponseRPL_INVITING();
    virtual ~IRCResponseRPL_INVITING();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetChannel(const std::string& channel) { m_Channel = channel; }
    inline const std::string& GetChannel(void) const { return m_Channel; }
    inline void SetNick(const std::string& nick) { m_Nick = nick; }
    inline const std::string& GetNick(void) const { return m_Nick; }

private:
    std::string m_Channel;
    std::string m_Nick;
};

}
