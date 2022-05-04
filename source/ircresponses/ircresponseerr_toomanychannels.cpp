#include "main/precomp.h"

#include "ircresponses/ircresponseerr_toomanychannels.h"

#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_TOOMANYCHANNELS::IRCResponseERR_TOOMANYCHANNELS(void) : IRCResponse(Enum_IRCResponses_ERR_TOOMANYCHANNELS)
{
    Initialize();
}

void IRCResponseERR_TOOMANYCHANNELS::Initialize(void)
{
}

IRCResponseERR_TOOMANYCHANNELS::~IRCResponseERR_TOOMANYCHANNELS()
{
    Shutdown();
}

void IRCResponseERR_TOOMANYCHANNELS::Shutdown(void)
{
}

std::string IRCResponseERR_TOOMANYCHANNELS::GetResponse(void) const
{
    std::string response;
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCCResponses>::From(GetResponseEnum());
    response += " " + m_ChannelName + " :You have joined too many channels";
    return response;
}


}
