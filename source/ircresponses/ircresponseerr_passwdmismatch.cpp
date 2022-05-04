#include "main/precomp.h"

#include "ircresponses/ircresponseerr_passwdmismatch.h"

#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_PASSWDMISMATCH::IRCResponseERR_PASSWDMISMATCH(void) : IRCResponse(Enum_IRCResponses_ERR_PASSWDMISMATCH)
{
    Initialize();
}

void IRCResponseERR_PASSWDMISMATCH::Initialize(void)
{
}

IRCResponseERR_PASSWDMISMATCH::~IRCResponseERR_PASSWDMISMATCH()
{
    Shutdown();
}

void IRCResponseERR_PASSWDMISMATCH::Shutdown(void)
{
}

std::string IRCResponseERR_PASSWDMISMATCH::GetResponse(void) const
{
    std::string response;
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " :Password incorrect";
    return response;
}


}
