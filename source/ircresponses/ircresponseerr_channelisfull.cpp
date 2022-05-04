#include "main/precomp.h"

#include "ircresponses/ircresponseerr_channelisfull.h"

#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_CHANNELISFULL::IRCResponseERR_CHANNELISFULL(void) : IRCResponse(Enum_IRCResponses_ERR_CHANNELISFULL)
{
    Initialize();
}

void IRCResponseERR_CHANNELISFULL::Initialize(void)
{
}

IRCResponseERR_CHANNELISFULL::~IRCResponseERR_CHANNELISFULL()
{
    Shutdown();
}

void IRCResponseERR_CHANNELISFULL::Shutdown(void)
{
}

std::string IRCResponseERR_CHANNELISFULL::GetResponse(void) const
{
    std::string response;
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " " + m_Channel + " :Cannot join channel (+l)";
    return response;
}


}
