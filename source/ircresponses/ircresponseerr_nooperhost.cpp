#include "main/precomp.h"

#include "ircresponses/ircresponseerr_nooperhost.h"
#include "ircresponses/ircresponses.h"

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
    response += " :No O-lines for your host\n";
    return response;
}


}
