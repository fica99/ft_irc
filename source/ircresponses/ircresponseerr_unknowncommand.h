#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_UNKNOWNCOMMAND : public IRCResponse
{
public:
    IRCResponseERR_UNKNOWNCOMMAND();
    virtual ~IRCResponseERR_UNKNOWNCOMMAND();
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
