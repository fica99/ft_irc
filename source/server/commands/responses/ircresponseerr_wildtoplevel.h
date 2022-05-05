#pragma once

#include <string>

#include "server/commands/responses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_WILDTOPLEVEL : public IRCResponse
{
public:
    IRCResponseERR_WILDTOPLEVEL();
    virtual ~IRCResponseERR_WILDTOPLEVEL();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetMask(const std::string& mask) { m_Mask = mask; }

private:
    std::string m_Mask;
};

}
