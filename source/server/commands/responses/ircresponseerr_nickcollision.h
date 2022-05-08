#pragma once

#include <string>

#include "server/commands/responses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_NICKCOLLISION : public IRCResponse
{
public:
    IRCResponseERR_NICKCOLLISION();
    virtual ~IRCResponseERR_NICKCOLLISION();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetNick(const std::string& nick) { m_Nick = nick; }

private:
    std::string m_Nick;
};

}
