#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseRPL_AWAY : public IRCResponse
{
public:
    IRCResponseRPL_AWAY();
    virtual ~IRCResponseRPL_AWAY();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetNick(const std::string& nick) { m_Nick = nick; }
    inline const std::string& GetNick(void) const { return m_Nick; }
    inline void SetAwayMessage(const std::string& awayMessage) { m_AwayMessage = awayMessage; }
    inline const std::string& GetAwayMessage(void) const { return m_AwayMessage; }

private:
    std::string m_Nick;
    std::string m_AwayMessage;
};

}
