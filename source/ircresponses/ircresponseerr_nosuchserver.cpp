#include "main/precomp.h"

#include "ircresponses/ircresponseerr_nosuchserver.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_NOSUCHSERVER::IRCResponseERR_NOSUCHSERVER(void) : IRCResponse(Enum_IRCResponses_ERR_NOSUCHSERVER)
{
    Initialize();
}

void IRCResponseERR_NOSUCHSERVER::Initialize(void)
{
}

IRCResponseERR_NOSUCHSERVER::~IRCResponseERR_NOSUCHSERVER()
{
    Shutdown();
}

void IRCResponseERR_NOSUCHSERVER::Shutdown(void)
{
}

std::string IRCResponseERR_NOSUCHSERVER::GetResponse(void) const
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
    response += " " + m_ServerName + " :No such server\n";
    return response;
}


}
