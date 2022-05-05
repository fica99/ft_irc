#pragma once

#include <string>
#include <vector>
#include <utility>

#include "server/commands/responses/ircresponse.h"

namespace ircserv
{

class IRCResponseRPL_LISTSTART : public IRCResponse
{
public:
    IRCResponseRPL_LISTSTART();
    virtual ~IRCResponseRPL_LISTSTART();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;
};

}
