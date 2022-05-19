#include "main/precomp.h"

#include "server/commands/responses/ircresponseerr_noprivileges.h"

#include "server/commands/responses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_NOPRIVILEGES::IRCResponseERR_NOPRIVILEGES(void) : IRCResponse(Enum_IRCResponses_ERR_NOPRIVILEGES)
{
    Initialize();
}

void IRCResponseERR_NOPRIVILEGES::Initialize(void)
{
}

IRCResponseERR_NOPRIVILEGES::~IRCResponseERR_NOPRIVILEGES()
{
    Shutdown();
}

void IRCResponseERR_NOPRIVILEGES::Shutdown(void)
{
}

std::string IRCResponseERR_NOPRIVILEGES::GetResponse(void) const
{
    std::string response;
    
    if (!GetPrefix().empty())
    {
        response += GetPrefix();
        response += " ";
    }
    response += EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " :Permission Denied- You're not an IRC operator";
    return response;
}


}
