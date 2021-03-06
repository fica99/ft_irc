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
    response += " " + m_ChannelName + " :You have joined too many channels\n";
    return response;
}


}
