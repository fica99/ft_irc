#include "main/precomp.h"

#include "server/commands/responses/ircresponserpl_liststart.h"

#include "server/commands/responses/ircresponses.h"

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
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " Channel :Users  Name";
    return response;
}


}
