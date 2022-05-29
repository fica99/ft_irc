#include "main/precomp.h"

#include "ircresponses/ircresponserpl_notopic.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseRPL_NOTOPIC::IRCResponseRPL_NOTOPIC(void) : IRCResponse(Enum_IRCResponses_RPL_NOTOPIC)
{
    Initialize();
}

void IRCResponseRPL_NOTOPIC::Initialize(void)
{
}

IRCResponseRPL_NOTOPIC::~IRCResponseRPL_NOTOPIC()
{
    Shutdown();
}

void IRCResponseRPL_NOTOPIC::Shutdown(void)
{
}

std::string IRCResponseRPL_NOTOPIC::GetResponse(void) const
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
    response += " " + m_Channel + " :No topic is set\n";
    return response;
}


}
