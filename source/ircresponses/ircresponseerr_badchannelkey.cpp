#include "main/precomp.h"

#include "ircresponses/ircresponseerr_badchannelkey.h"

#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_BADCHANNELKEY::IRCResponseERR_BADCHANNELKEY(void) : IRCResponse(Enum_IRCResponses_ERR_BADCHANNELKEY)
{
    Initialize();
}

void IRCResponseERR_BADCHANNELKEY::Initialize(void)
{
}

IRCResponseERR_BADCHANNELKEY::~IRCResponseERR_BADCHANNELKEY()
{
    Shutdown();
}

void IRCResponseERR_BADCHANNELKEY::Shutdown(void)
{
}

std::string IRCResponseERR_BADCHANNELKEY::GetResponse(void) const
{
    std::string response;
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCCResponses>::From(GetResponseEnum());
    response += " " + m_Channel + " :Cannot join channel (+k)";
    return response;
}


}
