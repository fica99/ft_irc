#include "main/precomp.h"

#include "server/commands/responses/ircresponserpl_endofnames.h"

#include "server/commands/responses/ircresponses.h"

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
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " " + m_Channel + " :End of /NAMES list";
    return response;
}


}
