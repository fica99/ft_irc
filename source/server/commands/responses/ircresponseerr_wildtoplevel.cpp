#include "main/precomp.h"

#include "server/commands/responses/ircresponseerr_wildtoplevel.h"

#include "server/commands/responses/ircresponses.h"

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
    response += " " + m_Mask + " :Wildcard in toplevel domain";
    return response;
}


}
