#pragma once


#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_NOMOTD : public IRCResponse
{
public:
    IRCResponseERR_NOMOTD();
    virtual ~IRCResponseERR_NOMOTD();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;
};

}
