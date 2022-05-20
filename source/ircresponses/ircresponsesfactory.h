#pragma once

#include "ircresponses/ircresponses.h"
#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponsesFactory
{
public:
    IRCResponsesFactory();
    virtual ~IRCResponsesFactory();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    IRCResponse* CreateResponse(Enum_IRCResponses responseType);
    void DestroyResponse(IRCResponse* response);
};

}