#include "main/precomp.h"

#include "ircresponses/ircresponserpl_motd.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseRPL_MOTD::IRCResponseRPL_MOTD(void) : IRCResponse(Enum_IRCResponses_RPL_MOTD)
{
    Initialize();
}

void IRCResponseRPL_MOTD::Initialize(void)
{
}

IRCResponseRPL_MOTD::~IRCResponseRPL_MOTD()
{
    Shutdown();
}

void IRCResponseRPL_MOTD::Shutdown(void)
{
}

std::string IRCResponseRPL_MOTD::GetResponse(void) const
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
    response += " :- " + GetText() + "\n";
    return response;
}


}
