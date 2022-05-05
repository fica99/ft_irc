#pragma once

#include <string>

#include "server/commands/responses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_NOOPERHOST : public IRCResponse
{
public:
    IRCResponseERR_NOOPERHOST();
    virtual ~IRCResponseERR_NOOPERHOST();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;
};

}
