#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_CANTKILLSERVER : public IRCResponse
{
public:
    IRCResponseERR_CANTKILLSERVER();
    virtual ~IRCResponseERR_CANTKILLSERVER();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;
};

}
