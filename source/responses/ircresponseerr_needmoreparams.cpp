#include "main/precomp.h"

#include "responses/ircresponseerr_needmoreparams.h"

#include "responses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_NEEDMOREPARAMS::IRCResponseERR_NEEDMOREPARAMS(void) : IRCResponse(Enum_IRCResponses_ERR_NEEDMOREPARAMS)
{
    Initialize();
}

void IRCResponseERR_NEEDMOREPARAMS::Initialize(void)
{
}

IRCResponseERR_NEEDMOREPARAMS::~IRCResponseERR_NEEDMOREPARAMS()
{
    Shutdown();
}

void IRCResponseERR_NEEDMOREPARAMS::Shutdown(void)
{
}

std::string IRCResponseERR_NEEDMOREPARAMS::GetResponse(void) const
{
    std::string response;
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " " + m_Command + " :Not enough parameters";
    return response;
}


}
