#pragma once

#include <string>
#include <vector>
#include <utility>

#include "server/commands/responses/ircresponse.h"

namespace ircserv
{

class IRCResponseRPL_LISTEND : public IRCResponse
{
public:
    IRCResponseRPL_LISTEND();
    virtual ~IRCResponseRPL_LISTEND();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;
};

}
