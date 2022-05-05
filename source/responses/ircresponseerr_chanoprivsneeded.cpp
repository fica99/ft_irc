#include "main/precomp.h"

#include "responses/ircresponseerr_chanoprivsneeded.h"

#include "responses/ircresponses.h"

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
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " " + m_Channel + " :You're not channel operator";
    return response;
}


}
