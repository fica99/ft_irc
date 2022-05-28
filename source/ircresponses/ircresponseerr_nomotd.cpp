#include "main/precomp.h"

#include "ircresponses/ircresponseerr_nomotd.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_NOMOTD::IRCResponseERR_NOMOTD(void) : IRCResponse(Enum_IRCResponses_ERR_NOMOTD)
{
    Initialize();
}

void IRCResponseERR_NOMOTD::Initialize(void)
{
}

IRCResponseERR_NOMOTD::~IRCResponseERR_NOMOTD()
{
    Shutdown();
}

void IRCResponseERR_NOMOTD::Shutdown(void)
{
}

std::string IRCResponseERR_NOMOTD::GetResponse(void) const
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
    response += " :MOTD File is missing\n";
    return response;
}


}
