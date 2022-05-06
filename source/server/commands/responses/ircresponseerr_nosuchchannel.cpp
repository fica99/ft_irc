#include "main/precomp.h"

#include "server/commands/responses/ircresponseerr_nosuchchannel.h"

#include "server/commands/responses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_NOSUCHCHANNEL::IRCResponseERR_NOSUCHCHANNEL(void) : IRCResponse(Enum_IRCResponses_ERR_NOSUCHCHANNEL)
{
    Initialize();
}

void IRCResponseERR_NOSUCHCHANNEL::Initialize(void)
{
}

IRCResponseERR_NOSUCHCHANNEL::~IRCResponseERR_NOSUCHCHANNEL()
{
    Shutdown();
}

void IRCResponseERR_NOSUCHCHANNEL::Shutdown(void)
{
}

std::string IRCResponseERR_NOSUCHCHANNEL::GetResponse(void) const
{
    std::string response;
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " " + m_ChannelName + " :No such channel";
    return response;
}


}
