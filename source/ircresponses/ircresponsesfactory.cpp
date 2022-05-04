#include "main/precomp.h"

#include "ircresponses/ircresponsesfactory.h"

#include "utils/memory.h"
#include "ircresponses/ircresponseerr_alreadyregistered.h"
#include "ircresponses/ircresponseerr_badchannelkey.h"
#include "ircresponses/ircresponseerr_bannedfromchan.h"
#include "ircresponses/ircresponseerr_channelisfull.h"
#include "ircresponses/ircresponseerr_erroneusnickname.h"
#include "ircresponses/ircresponseerr_inviteonlychan.h"
#include "ircresponses/ircresponseerr_needmoreparams.h"
#include "ircresponses/ircresponseerr_nickcollision.h"
#include "ircresponses/ircresponseerr_nicknameinuse.h"
#include "ircresponses/ircresponseerr_nonicknamegiven.h"
#include "ircresponses/ircresponseerr_nooperhost.h"
#include "ircresponses/ircresponseerr_nosuchchannel.h"
#include "ircresponses/ircresponseerr_notonchannel.h"
#include "ircresponses/ircresponseerr_passwdmismatch.h"
#include "ircresponses/ircresponseerr_toomanychannels.h"
#include "ircresponses/ircresponserpl_topic.h"
#include "ircresponses/ircresponserpl_youreoper.h"

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

IRCResponse* IRCResponsesFactory::CreateResponse(Enum_IRCResponses responseType)
{
    IRCResponse* response = NULL;
    switch (responseType)
    {
        case Enum_IRCResponses_ERR_ALREADYREGISTRED:
            response = New(IRCResponseERR_ALREADYREGISTERED)();
            break;
        case Enum_IRCResponses_ERR_BADCHANNELKEY:
            response = New(IRCResponseERR_BADCHANNELKEY)();
            break;
        case Enum_IRCResponses_ERR_BANNEDFROMCHAN:
            response = New(IRCResponseERR_BANNEDFROMCHAN)();
            break;
        case Enum_IRCResponses_ERR_CHANNELISFULL:
            response = New(IRCResponseERR_CHANNELISFULL)();
            break;
        case Enum_IRCResponses_ERR_ERRONEUSNICKNAME:
            response = New(IRCResponseERR_ERRONEUSNICKNAME)();
            break;
        case Enum_IRCResponses_ERR_INVITEONLYCHAN:
            response = New(IRCResponseERR_INVITEONLYCHAN)();
            break;
        case Enum_IRCResponses_ERR_NEEDMOREPARAMS:
            response = New(IRCResponseERR_NEEDMOREPARAMS)();
            break;
        case Enum_IRCResponses_ERR_NICKCOLLISION:
            response = New(IRCResponseERR_NICKCOLLISION)();
            break;
        case Enum_IRCResponses_ERR_NICKNAMEINUSE:
            response = New(IRCResponseERR_NICKNAMEINUSE)();
            break;
        case Enum_IRCResponses_ERR_NONICKNAMEGIVEN:
            response = New(IRCResponseERR_NONICKNAMEGIVEN)();
            break;
        case Enum_IRCResponses_ERR_NOOPERHOST:
            response = New(IRCResponseERR_NOOPERHOST)();
            break;
        case Enum_IRCResponses_ERR_NOSUCHCHANNEL:
            response = New(IRCResponseERR_NOSUCHCHANNEL)();
            break;
        case Enum_IRCResponses_ERR_NOTONCHANNEL:
            response = New(IRCResponseERR_NOTONCHANNEL)();
            break;
        case Enum_IRCResponses_ERR_PASSWDMISMATCH:
            response = New(IRCResponseERR_PASSWDMISMATCH)();
            break;
        case Enum_IRCResponses_ERR_TOOMANYCHANNELS:
            response = New(IRCResponseERR_TOOMANYCHANNELS)();
            break;
        case Enum_IRCResponses_RPL_TOPIC:
            response = New(IRCResponseRPL_TOPIC)();
            break;
        case Enum_IRCResponses_RPL_YOUREOPER:
            response = New(IRCResponseRPL_YOUREOPER)();
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
