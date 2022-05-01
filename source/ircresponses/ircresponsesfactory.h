#pragma once

#include "utils/singleton.h"
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
    DECLARE_SIMPLE_SINGLETON(IRCResponsesFactory);

public:
    IRCResponse* CreateResponse(Enum_IRCCResponses responseType = Enum_IRCResponses_Unknown,
                            const std::string& prefix = "",
                            const std::string& delimeter = " ");
    void DestroyResponse(IRCResponse* response);
};

#define GetIRCResponsesFactory() IRCResponsesFactory::GetInstance()

}
