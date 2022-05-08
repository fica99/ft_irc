#pragma once

#include <string>

#include "server/commands/responses/ircresponse.h"

namespace ircserv
{

class IRCResponseRPL_YOUREOPER : public IRCResponse
{
public:
    IRCResponseRPL_YOUREOPER();
    virtual ~IRCResponseRPL_YOUREOPER();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;
};

}
