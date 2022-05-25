#include "main/precomp.h"

#include "ircresponses/ircresponseerr_nonicknamegiven.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_NONICKNAMEGIVEN::IRCResponseERR_NONICKNAMEGIVEN(void) : IRCResponse(Enum_IRCResponses_ERR_NONICKNAMEGIVEN)
{
    Initialize();
}

void IRCResponseERR_NONICKNAMEGIVEN::Initialize(void)
{
}

IRCResponseERR_NONICKNAMEGIVEN::~IRCResponseERR_NONICKNAMEGIVEN()
{
    Shutdown();
}

void IRCResponseERR_NONICKNAMEGIVEN::Shutdown(void)
{
}

std::string IRCResponseERR_NONICKNAMEGIVEN::GetResponse(void) const
{
    std::string response;
    
    if (!GetPrefix().empty())
    {
        response += GetPrefix();
        response += " ";
    }
    response += EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " :No nickname given\n";
    return response;
}


}
