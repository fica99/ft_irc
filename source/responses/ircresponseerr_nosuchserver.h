#pragma once

#include <string>

#include "responses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_NOSUCHSERVER : public IRCResponse
{
public:
    IRCResponseERR_NOSUCHSERVER();
    virtual ~IRCResponseERR_NOSUCHSERVER();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetServerName(const std::string& serverName) { m_ServerName = serverName; }

private:
    std::string m_ServerName;
};

}
