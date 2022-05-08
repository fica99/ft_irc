#include "main/precomp.h"

#include "server/commands/responses/ircresponseerr_nooperhost.h"

#include "server/commands/responses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_NOOPERHOST::IRCResponseERR_NOOPERHOST(void) : IRCResponse(Enum_IRCResponses_ERR_NOOPERHOST)
{
    Initialize();
}

void IRCResponseERR_NOOPERHOST::Initialize(void)
{
}

IRCResponseERR_NOOPERHOST::~IRCResponseERR_NOOPERHOST()
{
    Shutdown();
}

void IRCResponseERR_NOOPERHOST::Shutdown(void)
{
}

std::string IRCResponseERR_NOOPERHOST::GetResponse(void) const
{
    std::string response;
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " :No O-lines for your host";
    return response;
}


}
