#include "main/precomp.h"

#include "server/commands/responses/ircresponseerr_nosuchnick.h"

#include "server/commands/responses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_NOSUCHNICK::IRCResponseERR_NOSUCHNICK(void) : IRCResponse(Enum_IRCResponses_ERR_NOSUCHNICK)
{
    Initialize();
}

void IRCResponseERR_NOSUCHNICK::Initialize(void)
{
}

IRCResponseERR_NOSUCHNICK::~IRCResponseERR_NOSUCHNICK()
{
    Shutdown();
}

void IRCResponseERR_NOSUCHNICK::Shutdown(void)
{
}

std::string IRCResponseERR_NOSUCHNICK::GetResponse(void) const
{
    std::string response;
    
    if (!GetPrefix().empty())
    {
        response += GetPrefix();
        response += " ";
    }
    response += EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " " + m_Nickname + " :No such nick/channel";
    return response;
}


}
