#include "main/precomp.h"

#include "server/commands/responses/ircresponse.h"

namespace ircserv
{

IRCResponse::IRCResponse(Enum_IRCResponses responseEnum) : m_ResponseEnum(responseEnum)
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
