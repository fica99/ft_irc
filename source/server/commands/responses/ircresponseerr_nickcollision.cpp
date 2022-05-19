#include "main/precomp.h"

#include "server/commands/responses/ircresponseerr_nickcollision.h"

#include "server/commands/responses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_NICKCOLLISION::IRCResponseERR_NICKCOLLISION(void) : IRCResponse(Enum_IRCResponses_ERR_NICKCOLLISION)
{
    Initialize();
}

void IRCResponseERR_NICKCOLLISION::Initialize(void)
{
}

IRCResponseERR_NICKCOLLISION::~IRCResponseERR_NICKCOLLISION()
{
    Shutdown();
}

void IRCResponseERR_NICKCOLLISION::Shutdown(void)
{
}

std::string IRCResponseERR_NICKCOLLISION::GetResponse(void) const
{
    std::string response;
    
    if (!GetPrefix().empty())
    {
        response += GetPrefix();
        response += " ";
    }
    response += EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " " + m_Nick + " :Nickname collision KILL";
    return response;
}


}
