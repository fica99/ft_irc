#pragma once

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_NOTREGISTERED : public IRCResponse
{
public:
    IRCResponseERR_NOTREGISTERED();
    virtual ~IRCResponseERR_NOTREGISTERED();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;
};

}
