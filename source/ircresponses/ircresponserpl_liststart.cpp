#include "main/precomp.h"

#include "ircresponses/ircresponserpl_liststart.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseRPL_LISTSTART::IRCResponseRPL_LISTSTART(void) : IRCResponse(Enum_IRCResponses_RPL_LISTSTART)
{
    Initialize();
}

void IRCResponseRPL_LISTSTART::Initialize(void)
{
}

IRCResponseRPL_LISTSTART::~IRCResponseRPL_LISTSTART()
{
    Shutdown();
}

void IRCResponseRPL_LISTSTART::Shutdown(void)
{
}

std::string IRCResponseRPL_LISTSTART::GetResponse(void) const
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
    response += " Channel :Users  Name\n";
    return response;
}


}
