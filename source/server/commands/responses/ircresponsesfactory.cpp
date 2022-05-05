#include "main/precomp.h"

#include "server/commands/responses/ircresponsesfactory.h"

#include "utils/memory.h"
#include "server/commands/responses/ircresponseerr_alreadyregistered.h"
#include "server/commands/responses/ircresponseerr_badchannelkey.h"
#include "server/commands/responses/ircresponseerr_bannedfromchan.h"
#include "server/commands/responses/ircresponseerr_cannotsendtochan.h"
#include "server/commands/responses/ircresponseerr_cantkillserver.h"
#include "server/commands/responses/ircresponseerr_channelisfull.h"
#include "server/commands/responses/ircresponseerr_chanoprivsneeded.h"
#include "server/commands/responses/ircresponseerr_erroneusnickname.h"
#include "server/commands/responses/ircresponseerr_inviteonlychan.h"
#include "server/commands/responses/ircresponseerr_needmoreparams.h"
#include "server/commands/responses/ircresponseerr_nickcollision.h"
#include "server/commands/responses/ircresponseerr_nicknameinuse.h"
#include "server/commands/responses/ircresponseerr_nonicknamegiven.h"
#include "server/commands/responses/ircresponseerr_nooperhost.h"
#include "server/commands/responses/ircresponseerr_noprivileges.h"
#include "server/commands/responses/ircresponseerr_norecipient.h"
#include "server/commands/responses/ircresponseerr_nosuchchannel.h"
#include "server/commands/responses/ircresponseerr_nosuchnick.h"
#include "server/commands/responses/ircresponseerr_nosuchserver.h"
#include "server/commands/responses/ircresponseerr_notexttosend.h"
#include "server/commands/responses/ircresponseerr_notonchannel.h"
#include "server/commands/responses/ircresponseerr_notoplevel.h"
#include "server/commands/responses/ircresponseerr_passwdmismatch.h"
#include "server/commands/responses/ircresponseerr_toomanychannels.h"
#include "server/commands/responses/ircresponseerr_toomanytargets.h"
#include "server/commands/responses/ircresponseerr_wildtoplevel.h"
#include "server/commands/responses/ircresponserpl_away.h"
#include "server/commands/responses/ircresponserpl_endofnames.h"
#include "server/commands/responses/ircresponserpl_list.h"
#include "server/commands/responses/ircresponserpl_listend.h"
#include "server/commands/responses/ircresponserpl_liststart.h"
#include "server/commands/responses/ircresponserpl_namreply.h"
#include "server/commands/responses/ircresponserpl_topic.h"
#include "server/commands/responses/ircresponserpl_youreoper.h"

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
        case Enum_IRCResponses_ERR_CANNOTSENDTOCHAN:
            response = New(IRCResponseERR_CANNOTSENDTOCHAN)();
            break;
        case Enum_IRCResponses_ERR_CANTKILLSERVER:
            response = New(IRCResponseERR_CANTKILLSERVER)();
            break;
        case Enum_IRCResponses_ERR_CHANNELISFULL:
            response = New(IRCResponseERR_CHANNELISFULL)();
            break;
        case Enum_IRCResponses_ERR_CHANOPRIVSNEEDED:
            response = New(IRCResponseERR_CHANOPRIVSNEEDED)();
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
        case Enum_IRCResponses_ERR_NOPRIVILEGES:
            response = New(IRCResponseERR_NOPRIVILEGES)();
            break;
        case Enum_IRCResponses_ERR_NORECIPIENT:
            response = New(IRCResponseERR_NORECIPIENT)();
            break;
        case Enum_IRCResponses_ERR_NOSUCHCHANNEL:
            response = New(IRCResponseERR_NOSUCHCHANNEL)();
            break;
        case Enum_IRCResponses_ERR_NOSUCHNICK:
            response = New(IRCResponseERR_NOSUCHNICK)();
            break;
        case Enum_IRCResponses_ERR_NOSUCHSERVER:
            response = New(IRCResponseERR_NOSUCHSERVER)();
            break;
        case Enum_IRCResponses_ERR_NOTEXTTOSEND:
            response = New(IRCResponseERR_NOTEXTTOSEND)();
            break;
        case Enum_IRCResponses_ERR_NOTONCHANNEL:
            response = New(IRCResponseERR_NOTONCHANNEL)();
            break;
        case Enum_IRCResponses_ERR_NOTOPLEVEL:
            response = New(IRCResponseERR_NOTOPLEVEL)();
            break;
        case Enum_IRCResponses_ERR_PASSWDMISMATCH:
            response = New(IRCResponseERR_PASSWDMISMATCH)();
            break;
        case Enum_IRCResponses_ERR_TOOMANYCHANNELS:
            response = New(IRCResponseERR_TOOMANYCHANNELS)();
            break;
        case Enum_IRCResponses_ERR_TOOMANYTARGETS:
            response = New(IRCResponseERR_TOOMANYTARGETS)();
            break;
        case Enum_IRCResponses_ERR_WILDTOPLEVEL:
            response = New(IRCResponseERR_WILDTOPLEVEL)();
            break;
        case Enum_IRCResponses_RPL_AWAY:
            response = New(IRCResponseRPL_AWAY)();
            break;
        case Enum_IRCResponses_RPL_ENDOFNAMES:
            response = New(IRCResponseRPL_ENDOFNAMES)();
            break;
        case Enum_IRCResponses_RPL_LIST:
            response = New(IRCResponseRPL_LIST)();
            break;
        case Enum_IRCResponses_RPL_LISTEND:
            response = New(IRCResponseRPL_LISTEND)();
            break;
        case Enum_IRCResponses_RPL_LISTSTART:
            response = New(IRCResponseRPL_LISTSTART)();
            break;
        case Enum_IRCResponses_RPL_NAMREPLY:
            response = New(IRCResponseRPL_NAMREPLY)();
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