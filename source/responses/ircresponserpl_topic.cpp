#include "main/precomp.h"

#include "responses/ircresponserpl_topic.h"

#include "responses/ircresponses.h"

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
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " " + m_Channel + " :" + m_Topic;
    return response;
}


}
