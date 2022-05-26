#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseRPL_MOTD : public IRCResponse
{
public:
    IRCResponseRPL_MOTD();
    virtual ~IRCResponseRPL_MOTD();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetText(const std::string& text) { m_Text = text; }

private:
    std::string m_Text;
};

}
