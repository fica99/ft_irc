#include "main/precomp.h"

#include "server/commands/responses/ircresponserpl_umodeis.h"

#include "server/commands/responses/ircresponses.h"

namespace ircserv
{

IRCResponseRPL_UMODEIS::IRCResponseRPL_UMODEIS(void) : IRCResponse(Enum_IRCResponses_RPL_UMODEIS)
{
    Initialize();
}

void IRCResponseRPL_UMODEIS::Initialize(void)
{
}

IRCResponseRPL_UMODEIS::~IRCResponseRPL_UMODEIS()
{
    Shutdown();
}

void IRCResponseRPL_UMODEIS::Shutdown(void)
{
}

std::string IRCResponseRPL_UMODEIS::GetResponse(void) const
{
    std::string response;
    
    if (!GetPrefix().empty())
    {
        response += GetPrefix();
        response += " ";
    }
    response += EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " " + m_UserModeString;
    return response;
}


}
