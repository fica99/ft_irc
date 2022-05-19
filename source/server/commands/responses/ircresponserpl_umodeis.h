#pragma once

#include <string>

#include "server/commands/responses/ircresponse.h"

namespace ircserv
{

class IRCResponseRPL_UMODEIS : public IRCResponse
{
public:
    IRCResponseRPL_UMODEIS();
    virtual ~IRCResponseRPL_UMODEIS();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetUserModeString(const std::string& userModeString) { m_UserModeString = userModeString; }

private:
    std::string m_UserModeString;
};

}
