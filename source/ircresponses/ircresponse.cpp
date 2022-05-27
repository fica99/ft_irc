#include "main/precomp.h"

#include "ircresponses/ircresponse.h"

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

void IRCResponse::Send(IRCSocket *socket)
{
    if (socket != NULL)
    {
        socket->Send(GetResponse());
        IRC_LOGD("Sent response: %s", GetResponse().c_str());
    }
}

}
