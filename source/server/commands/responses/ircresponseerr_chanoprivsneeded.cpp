#include "main/precomp.h"

#include "server/commands/responses/ircresponseerr_chanoprivsneeded.h"

#include "server/commands/responses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_CHANOPRIVSNEEDED::IRCResponseERR_CHANOPRIVSNEEDED(void) : IRCResponse(Enum_IRCResponses_ERR_CHANOPRIVSNEEDED)
{
    Initialize();
}

void IRCResponseERR_CHANOPRIVSNEEDED::Initialize(void)
{
}

IRCResponseERR_CHANOPRIVSNEEDED::~IRCResponseERR_CHANOPRIVSNEEDED()
{
    Shutdown();
}

void IRCResponseERR_CHANOPRIVSNEEDED::Shutdown(void)
{
}

std::string IRCResponseERR_CHANOPRIVSNEEDED::GetResponse(void) const
{
    std::string response;
    
    if (!GetPrefix().empty())
    {
        response += GetPrefix();
        response += " ";
    }
    response += EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " " + m_Channel + " :You're not channel operator";
    return response;
}


}
