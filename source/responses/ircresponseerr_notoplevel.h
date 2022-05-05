#pragma once

#include <string>

#include "responses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_NOTOPLEVEL : public IRCResponse
{
public:
    IRCResponseERR_NOTOPLEVEL();
    virtual ~IRCResponseERR_NOTOPLEVEL();
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
