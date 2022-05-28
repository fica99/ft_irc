#include "main/precomp.h"

#include "ircresponses/ircresponseerr_unknowncommand.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_UNKNOWNCOMMAND::IRCResponseERR_UNKNOWNCOMMAND(void) : IRCResponse(Enum_IRCResponses_ERR_UNKNOWNCOMMAND)
{
    Initialize();
}

void IRCResponseERR_UNKNOWNCOMMAND::Initialize(void)
{
}

IRCResponseERR_UNKNOWNCOMMAND::~IRCResponseERR_UNKNOWNCOMMAND()
{
    Shutdown();
}

void IRCResponseERR_UNKNOWNCOMMAND::Shutdown(void)
{
}

std::string IRCResponseERR_UNKNOWNCOMMAND::GetResponse(void) const
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
    response += " " + m_Command + " :Unknown command\n";
    return response;
}


}
