#include "main/precomp.h"

#include "ircresponses/ircresponseerr_wildtoplevel.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_WILDTOPLEVEL::IRCResponseERR_WILDTOPLEVEL(void) : IRCResponse(Enum_IRCResponses_ERR_WILDTOPLEVEL)
{
    Initialize();
}

void IRCResponseERR_WILDTOPLEVEL::Initialize(void)
{
}

IRCResponseERR_WILDTOPLEVEL::~IRCResponseERR_WILDTOPLEVEL()
{
    Shutdown();
}

void IRCResponseERR_WILDTOPLEVEL::Shutdown(void)
{
}

std::string IRCResponseERR_WILDTOPLEVEL::GetResponse(void) const
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
    response += " " + m_Mask + " :Wildcard in toplevel domain\n";
    return response;
}


}
