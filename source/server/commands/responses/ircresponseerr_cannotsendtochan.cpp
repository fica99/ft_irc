#include "main/precomp.h"

#include "server/commands/responses/ircresponseerr_cannotsendtochan.h"

#include "server/commands/responses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_CANNOTSENDTOCHAN::IRCResponseERR_CANNOTSENDTOCHAN(void) : IRCResponse(Enum_IRCResponses_ERR_CANNOTSENDTOCHAN)
{
    Initialize();
}

void IRCResponseERR_CANNOTSENDTOCHAN::Initialize(void)
{
}

IRCResponseERR_CANNOTSENDTOCHAN::~IRCResponseERR_CANNOTSENDTOCHAN()
{
    Shutdown();
}

void IRCResponseERR_CANNOTSENDTOCHAN::Shutdown(void)
{
}

std::string IRCResponseERR_CANNOTSENDTOCHAN::GetResponse(void) const
{
    std::string response;
    
    if (!GetPrefix().empty())
    {
        response += GetPrefix();
        response += " ";
    }
    response += EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " " + m_ChannelName + " :Cannot send to channel";
    return response;
}


}
