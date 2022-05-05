#pragma once

#include "utils/singleton.h"
#include "responses/ircresponses.h"
#include "responses/ircresponse.h"

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
    DECLARE_SIMPLE_SINGLETON(IRCResponsesFactory);

public:
    IRCResponse* CreateResponse(Enum_IRCResponses responseType = Enum_IRCResponses_Unknown);
    void DestroyResponse(IRCResponse* response);
};

#define GetIRCResponsesFactory() IRCResponsesFactory::GetInstance()

}
