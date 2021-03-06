#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_PASSWDMISMATCH : public IRCResponse
{
public:
    IRCResponseERR_PASSWDMISMATCH();
    virtual ~IRCResponseERR_PASSWDMISMATCH();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;
};

}
