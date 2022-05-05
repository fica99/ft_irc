#include "main/precomp.h"

#include "responses/ircresponseerr_notexttosend.h"

#include "responses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_NOTEXTTOSEND::IRCResponseERR_NOTEXTTOSEND(void) : IRCResponse(Enum_IRCResponses_ERR_NOTEXTTOSEND)
{
    Initialize();
}

void IRCResponseERR_NOTEXTTOSEND::Initialize(void)
{
}

IRCResponseERR_NOTEXTTOSEND::~IRCResponseERR_NOTEXTTOSEND()
{
    Shutdown();
}

void IRCResponseERR_NOTEXTTOSEND::Shutdown(void)
{
}

std::string IRCResponseERR_NOTEXTTOSEND::GetResponse(void) const
{
    std::string response;
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " :No text to send";
    return response;
}


}
