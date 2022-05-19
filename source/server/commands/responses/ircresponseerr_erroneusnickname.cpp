#include "main/precomp.h"

#include "server/commands/responses/ircresponseerr_erroneusnickname.h"

#include "server/commands/responses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_ERRONEUSNICKNAME::IRCResponseERR_ERRONEUSNICKNAME(void) : IRCResponse(Enum_IRCResponses_ERR_ERRONEUSNICKNAME)
{
    Initialize();
}

void IRCResponseERR_ERRONEUSNICKNAME::Initialize(void)
{
}

IRCResponseERR_ERRONEUSNICKNAME::~IRCResponseERR_ERRONEUSNICKNAME()
{
    Shutdown();
}

void IRCResponseERR_ERRONEUSNICKNAME::Shutdown(void)
{
}

std::string IRCResponseERR_ERRONEUSNICKNAME::GetResponse(void) const
{
    std::string response;
    
    if (!GetPrefix().empty())
    {
        response += GetPrefix();
        response += " ";
    }
    response += EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " " + m_Nick + " :Erroneus nickname";
    return response;
}


}
