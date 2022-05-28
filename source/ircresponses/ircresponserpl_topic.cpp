#include "main/precomp.h"

#include "ircresponses/ircresponserpl_topic.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseRPL_TOPIC::IRCResponseRPL_TOPIC(void) : IRCResponse(Enum_IRCResponses_RPL_TOPIC)
{
    Initialize();
}

void IRCResponseRPL_TOPIC::Initialize(void)
{
}

IRCResponseRPL_TOPIC::~IRCResponseRPL_TOPIC()
{
    Shutdown();
}

void IRCResponseRPL_TOPIC::Shutdown(void)
{
}

std::string IRCResponseRPL_TOPIC::GetResponse(void) const
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
    response += " " + m_Channel + " :" + m_Topic + "\n";
    return response;
}


}
