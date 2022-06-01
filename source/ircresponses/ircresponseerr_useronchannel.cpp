#include "main/precomp.h"

#include "ircresponses/ircresponseerr_useronchannel.h"

#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_USERONCHANNEL::IRCResponseERR_USERONCHANNEL(void) : IRCResponse(Enum_IRCResponses_ERR_USERONCHANNEL)
{
    Initialize();
}

void IRCResponseERR_USERONCHANNEL::Initialize(void)
{
}

IRCResponseERR_USERONCHANNEL::~IRCResponseERR_USERONCHANNEL()
{
    Shutdown();
}

void IRCResponseERR_USERONCHANNEL::Shutdown(void)
{
}

std::string IRCResponseERR_USERONCHANNEL::GetResponse(void) const
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
    response += " " + GetUser() + " " + GetChannel() + " :is already on channel\n";
    return response;
}


}
