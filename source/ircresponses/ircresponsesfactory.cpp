#include "main/precomp.h"

#include "ircresponses/ircresponsesfactory.h"

#include "utils/memory.h"
#include "ircresponses/ircresponseerr_needmoreparams.h"
#include "ircresponses/ircresponseerr_nonicknamegiven.h"

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

IRCResponse* IRCResponsesFactory::CreateResponse(Enum_IRCCResponses responseType)
{
    IRCResponse* response = NULL;
    switch (responseType)
    {
        case Enum_IRCResponses_ERR_NEEDMOREPARAMS:
            response = New(IRCResponseERR_NEEDMOREPARAMS)();
            break;
        case Enum_IRCResponses_ERR_NONICKNAMEGIVEN:
            response = New(IRCResponseERR_NONICKNAMEGIVEN)();
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