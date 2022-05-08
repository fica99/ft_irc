#include "main/precomp.h"

#include "server/commands/responses/ircresponseerr_inviteonlychan.h"

#include "server/commands/responses/ircresponses.h"

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
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " " + m_Channel + " :Cannot join channel (+i)";
    return response;
}


}
