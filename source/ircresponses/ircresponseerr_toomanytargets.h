#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_TOOMANYTARGETS : public IRCResponse
{
public:
    IRCResponseERR_TOOMANYTARGETS();
    virtual ~IRCResponseERR_TOOMANYTARGETS();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetTarget(const std::string& target) { m_Target = target; }

private:
    std::string m_Target;
};

}
