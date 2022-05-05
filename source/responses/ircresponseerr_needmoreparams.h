#pragma once

#include <string>

#include "responses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_NEEDMOREPARAMS : public IRCResponse
{
public:
    IRCResponseERR_NEEDMOREPARAMS();
    virtual ~IRCResponseERR_NEEDMOREPARAMS();
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
