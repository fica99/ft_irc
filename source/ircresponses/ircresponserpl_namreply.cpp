#include "main/precomp.h"

#include "ircresponses/ircresponserpl_namreply.h"
#include "ircresponses/ircresponses.h"

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
    return response + '\n';
}


}
