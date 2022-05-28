#include "main/precomp.h"

#include "ircresponses/ircresponserpl_endofmotd.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseRPL_ENDOFMOTD::IRCResponseRPL_ENDOFMOTD(void) : IRCResponse(Enum_IRCResponses_RPL_ENDOFMOTD)
{
    Initialize();
}

void IRCResponseRPL_ENDOFMOTD::Initialize(void)
{
}

IRCResponseRPL_ENDOFMOTD::~IRCResponseRPL_ENDOFMOTD()
{
    Shutdown();
}

void IRCResponseRPL_ENDOFMOTD::Shutdown(void)
{
}

std::string IRCResponseRPL_ENDOFMOTD::GetResponse(void) const
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
    response += " :End of /MOTD command\n";
    return response;
}


}
