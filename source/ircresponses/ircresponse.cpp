#include "main/precomp.h"

#include "ircresponses/ircresponse.h"

namespace ircserv
{

IRCResponse::IRCResponse(Enum_IRCCResponses responseType, const std::string& prefix, const std::string& delimeter)
    : m_ResponseType(responseType)
    , m_Prefix(prefix)
    , m_Delimeter(delimeter)
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
