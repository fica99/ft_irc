#include "main/precomp.h"

#include "ircresponses/ircresponserpl_inviting.h"

#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseRPL_INVITING::IRCResponseRPL_INVITING(void) : IRCResponse(Enum_IRCResponses_RPL_INVITING)
{
    Initialize();
}

void IRCResponseRPL_INVITING::Initialize(void)
{
}

IRCResponseRPL_INVITING::~IRCResponseRPL_INVITING()
{
    Shutdown();
}

void IRCResponseRPL_INVITING::Shutdown(void)
{
}

std::string IRCResponseRPL_INVITING::GetResponse(void) const
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
    response += " " + GetChannel() + " " + GetNick() + "\n";
    return response;
}


}
