#include "main/precomp.h"

#include "ircresponses/ircresponseerr_bannedfromchan.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_BANNEDFROMCHAN::IRCResponseERR_BANNEDFROMCHAN(void) : IRCResponse(Enum_IRCResponses_ERR_BANNEDFROMCHAN)
{
    Initialize();
}

void IRCResponseERR_BANNEDFROMCHAN::Initialize(void)
{
}

IRCResponseERR_BANNEDFROMCHAN::~IRCResponseERR_BANNEDFROMCHAN()
{
    Shutdown();
}

void IRCResponseERR_BANNEDFROMCHAN::Shutdown(void)
{
}

std::string IRCResponseERR_BANNEDFROMCHAN::GetResponse(void) const
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
    response += " " + m_Channel + " :Cannot join channel (+b)\n";
    return response;
}


}
