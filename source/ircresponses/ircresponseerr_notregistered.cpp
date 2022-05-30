#include "main/precomp.h"

#include "ircresponses/ircresponseerr_notregistered.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_NOTREGISTERED::IRCResponseERR_NOTREGISTERED(void) : IRCResponse(Enum_IRCResponses_ERR_NOTREGISTERED)
{
    Initialize();
}

void IRCResponseERR_NOTREGISTERED::Initialize(void)
{
}

IRCResponseERR_NOTREGISTERED::~IRCResponseERR_NOTREGISTERED()
{
    Shutdown();
}

void IRCResponseERR_NOTREGISTERED::Shutdown(void)
{
}

std::string IRCResponseERR_NOTREGISTERED::GetResponse(void) const
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
    response += " :You have not registered\n";
    return response;
}


}
