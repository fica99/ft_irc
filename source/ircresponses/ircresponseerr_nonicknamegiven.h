#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_NONICKNAMEGIVEN : public IRCResponse
{
public:
    IRCResponseERR_NONICKNAMEGIVEN();
    virtual ~IRCResponseERR_NONICKNAMEGIVEN();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;
};

}
