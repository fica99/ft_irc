#include "main/precomp.h"

#include "responses/ircresponseerr_nooperhost.h"

#include "responses/ircresponses.h"

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
