#pragma once

#include <string>

#include "server/commands/responses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_NOTEXTTOSEND : public IRCResponse
{
public:
    IRCResponseERR_NOTEXTTOSEND();
    virtual ~IRCResponseERR_NOTEXTTOSEND();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;
};

}
