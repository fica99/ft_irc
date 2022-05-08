#pragma once

#include <string>

#include "server/commands/responses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_NORECIPIENT : public IRCResponse
{
public:
    IRCResponseERR_NORECIPIENT();
    virtual ~IRCResponseERR_NORECIPIENT();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetCommand(const std::string& command) { m_Command = command; }

private:
    std::string m_Command;
};

}
