#include "main/precomp.h"

#include "ircresponses/ircresponsesfactory.h"

#include "utils/memory.h"
#include "ircresponses/ircresponserpl_welcome.h"

namespace ircserv
{

IMPLEMENT_SIMPLE_SINGLETON(IRCResponsesFactory);

IRCResponsesFactory::IRCResponsesFactory()
{
    IMPLEMENT_SIMPLE_SINGLETON_CONSTRUCTOR();

    Initialize();
}

void IRCResponsesFactory::Initialize(void)
{
}

IRCResponsesFactory::~IRCResponsesFactory()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void IRCResponsesFactory::Shutdown(void)
{
}

IRCResponse* IRCResponsesFactory::CreateResponse(
    Enum_IRCCResponses responseType,
    const std::string& prefix,
    const std::string& delimeter)
{
    IRCResponse* response = NULL;
    switch (responseType)
    {
        case Enum_IRCResponses_RPL_WELCOME:
            response = New(IRCResponseRPL_WELCOME)(prefix, delimeter);
            break;
        default:
            response = NULL;
            break;
    }
    return response;
}

void IRCResponsesFactory::DestroyResponse(IRCResponse* response)
{ 
    if (response != NULL)
    {
        Delete(response);
    }
}

}
