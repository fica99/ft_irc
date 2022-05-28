#include "main/precomp.h"

#include "ircresponses/ircresponseerr_alreadyregistered.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_ALREADYREGISTERED::IRCResponseERR_ALREADYREGISTERED(void) : IRCResponse(Enum_IRCResponses_ERR_ALREADYREGISTRED)
{
    Initialize();
}

void IRCResponseERR_ALREADYREGISTERED::Initialize(void)
{
}

IRCResponseERR_ALREADYREGISTERED::~IRCResponseERR_ALREADYREGISTERED()
{
    Shutdown();
}

void IRCResponseERR_ALREADYREGISTERED::Shutdown(void)
{
}

std::string IRCResponseERR_ALREADYREGISTERED::GetResponse(void) const
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
    response += " :You may not reregister\n";
    return response;
}


}
