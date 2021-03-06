#include "main/precomp.h"

#include "ircresponses/ircresponseerr_nicknameinuse.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_NICKNAMEINUSE::IRCResponseERR_NICKNAMEINUSE(void) : IRCResponse(Enum_IRCResponses_ERR_NICKNAMEINUSE)
{
    Initialize();
}

void IRCResponseERR_NICKNAMEINUSE::Initialize(void)
{
}

IRCResponseERR_NICKNAMEINUSE::~IRCResponseERR_NICKNAMEINUSE()
{
    Shutdown();
}

void IRCResponseERR_NICKNAMEINUSE::Shutdown(void)
{
}

std::string IRCResponseERR_NICKNAMEINUSE::GetResponse(void) const
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
    response += " " + GetNick() + " :Nickname is already in use\n";
    return response;
}


}
