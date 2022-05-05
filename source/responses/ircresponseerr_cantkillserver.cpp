#include "main/precomp.h"

#include "responses/ircresponseerr_cantkillserver.h"

#include "responses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_CANTKILLSERVER::IRCResponseERR_CANTKILLSERVER(void) : IRCResponse(Enum_IRCResponses_ERR_CANTKILLSERVER)
{
    Initialize();
}

void IRCResponseERR_CANTKILLSERVER::Initialize(void)
{
}

IRCResponseERR_CANTKILLSERVER::~IRCResponseERR_CANTKILLSERVER()
{
    Shutdown();
}

void IRCResponseERR_CANTKILLSERVER::Shutdown(void)
{
}

std::string IRCResponseERR_CANTKILLSERVER::GetResponse(void) const
{
    std::string response;
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " :You cant kill a server!";
    return response;
}


}
