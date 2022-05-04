#include "main/precomp.h"

#include "ircresponses/ircresponse.h"

namespace ircserv
{

IRCResponse::IRCResponse(Enum_IRCCResponses responseEnum) : m_ResponseEnum(responseEnum)
{
    Initialize();
}

void IRCResponse::Initialize(void)
{
}

IRCResponse::~IRCResponse()
{
    Shutdown();
}

void IRCResponse::Shutdown(void)
{
}

}
