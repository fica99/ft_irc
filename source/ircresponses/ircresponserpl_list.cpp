#include "main/precomp.h"

#include "ircresponses/ircresponserpl_list.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseRPL_LIST::IRCResponseRPL_LIST(void) : IRCResponse(Enum_IRCResponses_RPL_LIST)
{
    Initialize();
}

void IRCResponseRPL_LIST::Initialize(void)
{
}

IRCResponseRPL_LIST::~IRCResponseRPL_LIST()
{
    Shutdown();
}

void IRCResponseRPL_LIST::Shutdown(void)
{
}

std::string IRCResponseRPL_LIST::GetResponse(void) const
{
    std::string response;
    
    if (!GetPrefix().empty())
    {
        response += GetPrefix();
        response += " ";
    }
    response += EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    // add visiable
    if (!GetNickname().empty())
    {
        response += " " + GetNickname();
    }
    response += " " + m_Channel + " " + m_NbVisible + " :" + m_Topic + "\n";
    return response;
}


}
