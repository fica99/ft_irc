#include "main/precomp.h"

#include "ircresponses/ircresponseerr_nonicknamegiven.h"

#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_NONICKNAMEGIVEN::IRCResponseERR_NONICKNAMEGIVEN(void) : IRCResponse(Enum_IRCResponses_ERR_NONICKNAMEGIVEN)
{
    Initialize();
}

void IRCResponseERR_NONICKNAMEGIVEN::Initialize(void)
{
}

IRCResponseERR_NONICKNAMEGIVEN::~IRCResponseERR_NONICKNAMEGIVEN()
{
    Shutdown();
}

void IRCResponseERR_NONICKNAMEGIVEN::Shutdown(void)
{
}

std::string IRCResponseERR_NONICKNAMEGIVEN::GetResponse(void) const
{
    std::string response;
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCCResponses>::From(GetResponseEnum());
    response += " :No nickname given";
    return response;
}


}
