#include "main/precomp.h"

#include "server/commands/responses/ircresponserpl_away.h"

#include "server/commands/responses/ircresponses.h"

namespace ircserv
{

IRCResponseRPL_AWAY::IRCResponseRPL_AWAY(void) : IRCResponse(Enum_IRCResponses_RPL_AWAY)
{
    Initialize();
}

void IRCResponseRPL_AWAY::Initialize(void)
{
}

IRCResponseRPL_AWAY::~IRCResponseRPL_AWAY()
{
    Shutdown();
}

void IRCResponseRPL_AWAY::Shutdown(void)
{
}

std::string IRCResponseRPL_AWAY::GetResponse(void) const
{
    std::string response;
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " " + m_Nick + " :" + m_AwayMessage;
    return response;
}


}