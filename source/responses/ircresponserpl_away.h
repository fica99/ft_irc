#pragma once

#include <string>

#include "responses/ircresponse.h"

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
    inline void SetAwayMessage(const std::string& awayMessage) { m_AwayMessage = awayMessage; }

private:
    std::string m_Nick;
    std::string m_AwayMessage;
};

}
