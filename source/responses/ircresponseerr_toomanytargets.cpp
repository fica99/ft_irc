#include "main/precomp.h"

#include "responses/ircresponseerr_toomanytargets.h"

#include "responses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_TOOMANYTARGETS::IRCResponseERR_TOOMANYTARGETS(void) : IRCResponse(Enum_IRCResponses_ERR_TOOMANYTARGETS)
{
    Initialize();
}

void IRCResponseERR_TOOMANYTARGETS::Initialize(void)
{
}

IRCResponseERR_TOOMANYTARGETS::~IRCResponseERR_TOOMANYTARGETS()
{
    Shutdown();
}

void IRCResponseERR_TOOMANYTARGETS::Shutdown(void)
{
}

std::string IRCResponseERR_TOOMANYTARGETS::GetResponse(void) const
{
    std::string response;
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " " + m_Target + " :Duplicate recipients. No message delivered";
    return response;
}


}
