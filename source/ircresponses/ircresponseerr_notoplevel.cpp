#include "main/precomp.h"

#include "ircresponses/ircresponseerr_notoplevel.h"

#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_NOTOPLEVEL::IRCResponseERR_NOTOPLEVEL(void) : IRCResponse(Enum_IRCResponses_ERR_NOTOPLEVEL)
{
    Initialize();
}

void IRCResponseERR_NOTOPLEVEL::Initialize(void)
{
}

IRCResponseERR_NOTOPLEVEL::~IRCResponseERR_NOTOPLEVEL()
{
    Shutdown();
}

void IRCResponseERR_NOTOPLEVEL::Shutdown(void)
{
}

std::string IRCResponseERR_NOTOPLEVEL::GetResponse(void) const
{
    std::string response;
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " " + m_Mask + " :No toplevel domain specified";
    return response;
}


}