#include "main/precomp.h"

#include "ircresponses/ircresponseerr_inviteonlychan.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_INVITEONLYCHAN::IRCResponseERR_INVITEONLYCHAN(void) : IRCResponse(Enum_IRCResponses_ERR_INVITEONLYCHAN)
{
    Initialize();
}

void IRCResponseERR_INVITEONLYCHAN::Initialize(void)
{
}

IRCResponseERR_INVITEONLYCHAN::~IRCResponseERR_INVITEONLYCHAN()
{
    Shutdown();
}

void IRCResponseERR_INVITEONLYCHAN::Shutdown(void)
{
}

std::string IRCResponseERR_INVITEONLYCHAN::GetResponse(void) const
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
    response += " " + m_Channel + " :Cannot join channel (+i)\n";
    return response;
}


}
