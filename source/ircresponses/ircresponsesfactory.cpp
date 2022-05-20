#include "main/precomp.h"

#include "ircresponses/ircresponsesfactory.h"

#include "ircresponses/ircresponseerr_alreadyregistered.h"
#include "ircresponses/ircresponseerr_badchannelkey.h"
#include "ircresponses/ircresponseerr_bannedfromchan.h"
#include "ircresponses/ircresponseerr_cannotsendtochan.h"
#include "ircresponses/ircresponseerr_cantkillserver.h"
#include "ircresponses/ircresponseerr_channelisfull.h"
#include "ircresponses/ircresponseerr_chanoprivsneeded.h"
#include "ircresponses/ircresponseerr_erroneusnickname.h"
#include "ircresponses/ircresponseerr_inviteonlychan.h"
#include "ircresponses/ircresponseerr_needmoreparams.h"
#include "ircresponses/ircresponseerr_nickcollision.h"
#include "ircresponses/ircresponseerr_nicknameinuse.h"
#include "ircresponses/ircresponseerr_nonicknamegiven.h"
#include "ircresponses/ircresponseerr_nooperhost.h"
#include "ircresponses/ircresponseerr_noprivileges.h"
#include "ircresponses/ircresponseerr_norecipient.h"
#include "ircresponses/ircresponseerr_nosuchchannel.h"
#include "ircresponses/ircresponseerr_nosuchnick.h"
#include "ircresponses/ircresponseerr_nosuchserver.h"
#include "ircresponses/ircresponseerr_notexttosend.h"
#include "ircresponses/ircresponseerr_notonchannel.h"
#include "ircresponses/ircresponseerr_notoplevel.h"
#include "ircresponses/ircresponseerr_passwdmismatch.h"
#include "ircresponses/ircresponseerr_toomanychannels.h"
#include "ircresponses/ircresponseerr_toomanytargets.h"
#include "ircresponses/ircresponseerr_wildtoplevel.h"
#include "ircresponses/ircresponserpl_away.h"
#include "ircresponses/ircresponserpl_endofnames.h"
#include "ircresponses/ircresponserpl_list.h"
#include "ircresponses/ircresponserpl_listend.h"
#include "ircresponses/ircresponserpl_liststart.h"
#include "ircresponses/ircresponserpl_namreply.h"
#include "ircresponses/ircresponserpl_topic.h"
#include "ircresponses/ircresponserpl_umodeis.h"
#include "ircresponses/ircresponserpl_youreoper.h"

#include "utils/memory.h"

namespace ircserv
{

IRCResponsesFactory::IRCResponsesFactory()
{
    Initialize();
}

void IRCResponsesFactory::Initialize(void)
{
}

IRCResponsesFactory::~IRCResponsesFactory()
{
    Shutdown();
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
        case Enum_IRCResponses_RPL_UMODEIS:
            response = New(IRCResponseRPL_UMODEIS)();
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