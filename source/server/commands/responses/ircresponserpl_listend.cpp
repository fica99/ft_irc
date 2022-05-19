#include "main/precomp.h"

#include "server/commands/responses/ircresponserpl_listend.h"

#include "server/commands/responses/ircresponses.h"

namespace ircserv
{

IRCResponseRPL_LISTEND::IRCResponseRPL_LISTEND(void) : IRCResponse(Enum_IRCResponses_RPL_LISTEND)
{
    Initialize();
}

void IRCResponseRPL_LISTEND::Initialize(void)
{
}

IRCResponseRPL_LISTEND::~IRCResponseRPL_LISTEND()
{
    Shutdown();
}

void IRCResponseRPL_LISTEND::Shutdown(void)
{
}

std::string IRCResponseRPL_LISTEND::GetResponse(void) const
{
    std::string response;
    
    if (!GetPrefix().empty())
    {
        response += GetPrefix();
        response += " ";
    }
    response += EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " :End of /LIST";
    return response;
}


}
