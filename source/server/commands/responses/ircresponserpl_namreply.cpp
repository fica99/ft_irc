#include "main/precomp.h"

#include "server/commands/responses/ircresponserpl_namreply.h"

#include "server/commands/responses/ircresponses.h"

namespace ircserv
{

IRCResponseRPL_NAMREPLY::IRCResponseRPL_NAMREPLY(void) : IRCResponse(Enum_IRCResponses_RPL_NAMREPLY)
{
    Initialize();
}

void IRCResponseRPL_NAMREPLY::Initialize(void)
{
}

IRCResponseRPL_NAMREPLY::~IRCResponseRPL_NAMREPLY()
{
    Shutdown();
}

void IRCResponseRPL_NAMREPLY::Shutdown(void)
{
}

std::string IRCResponseRPL_NAMREPLY::GetResponse(void) const
{
    std::string response;
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " " + m_Channel + " :";
    for (size_t i = 0; i < m_Nicks.size(); ++i)
    {
        if (m_Nicks[i].first == true)
        {
            response += "@";
        }
        else
        {
            response += "+";
        }
        response += m_Nicks[i].second;
        if (i != m_Nicks.size() - 1)
        {
            response += " ";
        }
    }
    return response;
}


}
