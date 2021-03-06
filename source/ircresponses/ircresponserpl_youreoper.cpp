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
    
    if (!GetPrefix().empty())
    {
        response += GetPrefix();
        response += " ";
    }
    response += EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    if (!GetNickname().empty())
    {
        response += " " + GetNickname();
    }
    response += " :You are now an IRC operator\n";
    return response;
}


}
