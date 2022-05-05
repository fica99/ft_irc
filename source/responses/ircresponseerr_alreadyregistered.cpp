#include "main/precomp.h"

#include "responses/ircresponseerr_alreadyregistered.h"

#include "responses/ircresponses.h"

namespace ircserv
{

IRCResponseERR_ALREADYREGISTERED::IRCResponseERR_ALREADYREGISTERED(void) : IRCResponse(Enum_IRCResponses_ERR_ALREADYREGISTRED)
{
    Initialize();
}

void IRCResponseERR_ALREADYREGISTERED::Initialize(void)
{
}

IRCResponseERR_ALREADYREGISTERED::~IRCResponseERR_ALREADYREGISTERED()
{
    Shutdown();
}

void IRCResponseERR_ALREADYREGISTERED::Shutdown(void)
{
}

std::string IRCResponseERR_ALREADYREGISTERED::GetResponse(void) const
{
    std::string response;
    
    response += GetPrefix();
    response += " " + EnumString<Enum_IRCResponses>::From(GetResponseEnum());
    response += " :You may not reregister";
    return response;
}


}
