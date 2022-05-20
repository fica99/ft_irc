#include "main/precomp.h"

#include "ircresponses/ircresponseerr_notonchannel.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_NOTONCHANNEL::IRCResponseERR_NOTONCHANNEL(void) : IRCResponse(Enum_IRCResponses_ERR_NOTONCHANNEL)
{
    Initialize();
}

void IRCResponseERR_NOTONCHANNEL::Initialize(void)
{
}

IRCResponseERR_NOTONCHANNEL::~IRCResponseERR_NOTONCHANNEL()
{
    Shutdown();
}

void IRCResponseERR_NOTONCHANNEL::Shutdown(void)
{
}

std::string IRCResponseERR_NOTONCHANNEL::GetResponse(void) const
{
    std::string response;
    
    if (!GetPrefix().empty())
    {
        response += GetPrefix();
        response += " ";
    }
    response += EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " " + m_Channel + " :You're not on that channel";
    return response;
}


}
