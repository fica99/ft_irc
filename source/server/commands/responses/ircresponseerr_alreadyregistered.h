#pragma once

#include <string>

#include "server/commands/responses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_ALREADYREGISTERED : public IRCResponse
{
public:
    IRCResponseERR_ALREADYREGISTERED();
    virtual ~IRCResponseERR_ALREADYREGISTERED();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;
};

}
