#pragma once

#include <string>

#include "server/commands/responses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_NOPRIVILEGES : public IRCResponse
{
public:
    IRCResponseERR_NOPRIVILEGES();
    virtual ~IRCResponseERR_NOPRIVILEGES();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;
};

}
