#include "main/precomp.h"

#include "ircresponses/ircresponserpl_endofnames.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseRPL_ENDOFNAMES::IRCResponseRPL_ENDOFNAMES(void) : IRCResponse(Enum_IRCResponses_RPL_ENDOFNAMES)
{
    Initialize();
}

void IRCResponseRPL_ENDOFNAMES::Initialize(void)
{
}

IRCResponseRPL_ENDOFNAMES::~IRCResponseRPL_ENDOFNAMES()
{
    Shutdown();
}

void IRCResponseRPL_ENDOFNAMES::Shutdown(void)
{
}

std::string IRCResponseRPL_ENDOFNAMES::GetResponse(void) const
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
    response += " " + m_Channel + " :End of /NAMES list\n";
    return response;
}


}
