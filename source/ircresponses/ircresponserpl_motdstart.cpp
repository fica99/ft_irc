#include "main/precomp.h"

#include "ircresponses/ircresponserpl_motdstart.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseRPL_MOTDSTART::IRCResponseRPL_MOTDSTART(void) : IRCResponse(Enum_IRCResponses_RPL_MOTDSTART)
{
    Initialize();
}

void IRCResponseRPL_MOTDSTART::Initialize(void)
{
}

IRCResponseRPL_MOTDSTART::~IRCResponseRPL_MOTDSTART()
{
    Shutdown();
}

void IRCResponseRPL_MOTDSTART::Shutdown(void)
{
}

std::string IRCResponseRPL_MOTDSTART::GetResponse(void) const
{
    std::string response;
    
    if (!GetPrefix().empty())
    {
        response += GetPrefix();
        response += " ";
    }
    response += EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " :- " + m_Server + " Message of the day - \n";
    return response;
}


}
