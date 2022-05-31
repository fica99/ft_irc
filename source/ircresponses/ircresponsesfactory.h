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
    static IRCResponse* CreateResponse(Enum_IRCResponses responseType, const std::string& arg1 = "", const std::string& arg2 = "", const std::string& arg3 = "");
    static void DestroyResponse(IRCResponse* response);
};

}
