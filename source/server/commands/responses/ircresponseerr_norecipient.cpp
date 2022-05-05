#include "main/precomp.h"

#include "server/commands/responses/ircresponseerr_norecipient.h"

#include "server/commands/responses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_NORECIPIENT::IRCResponseERR_NORECIPIENT(void) : IRCResponse(Enum_IRCResponses_ERR_NORECIPIENT)
{
    Initialize();
}

void IRCResponseERR_NORECIPIENT::Initialize(void)
{
}

IRCResponseERR_NORECIPIENT::~IRCResponseERR_NORECIPIENT()
{
    Shutdown();
}

void IRCResponseERR_NORECIPIENT::Shutdown(void)
{
}

std::string IRCResponseERR_NORECIPIENT::GetResponse(void) const
{
    std::string response;
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " :No recipient given (" + m_Command + ")";
    return response;
}


}
