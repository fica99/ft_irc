#include "main/precomp.h"

#include "ircresponses/ircresponserpl_youreoper.h"

#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseRPL_YOUREOPER::IRCResponseRPL_YOUREOPER(void) : IRCResponse(Enum_IRCResponses_RPL_YOUREOPER)
{
    Initialize();
}

void IRCResponseRPL_YOUREOPER::Initialize(void)
{
}

IRCResponseRPL_YOUREOPER::~IRCResponseRPL_YOUREOPER()
{
    Shutdown();
}

void IRCResponseRPL_YOUREOPER::Shutdown(void)
{
}

std::string IRCResponseRPL_YOUREOPER::GetResponse(void) const
{
    std::string response;
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " :You are now an IRC operator";
    return response;
}


}
