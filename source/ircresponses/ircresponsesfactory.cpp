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
#include "ircresponses/ircresponseerr_nomotd.h"
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
#include "ircresponses/ircresponseerr_notregistered.h"
#include "ircresponses/ircresponseerr_passwdmismatch.h"
#include "ircresponses/ircresponseerr_toomanychannels.h"
#include "ircresponses/ircresponseerr_toomanytargets.h"
#include "ircresponses/ircresponseerr_unknowncommand.h"
#include "ircresponses/ircresponseerr_useronchannel.h"
#include "ircresponses/ircresponseerr_wildtoplevel.h"
#include "ircresponses/ircresponserpl_away.h"
#include "ircresponses/ircresponserpl_endofmotd.h"
#include "ircresponses/ircresponserpl_endofnames.h"
#include "ircresponses/ircresponserpl_inviting.h"
#include "ircresponses/ircresponserpl_list.h"
#include "ircresponses/ircresponserpl_listend.h"
#include "ircresponses/ircresponserpl_liststart.h"
#include "ircresponses/ircresponserpl_motd.h"
#include "ircresponses/ircresponserpl_motdstart.h"
#include "ircresponses/ircresponserpl_namreply.h"
#include "ircresponses/ircresponserpl_notopic.h"
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

IRCResponse* IRCResponsesFactory::CreateResponse(Enum_IRCResponses responseType, const std::string& arg1, const std::string& arg2, const std::string& arg3)
{
    IRCResponse* response = NULL;
    switch (responseType)
    {
        case Enum_IRCResponses_ERR_ALREADYREGISTRED:
        {
            IRCResponseERR_ALREADYREGISTERED* dynamicResponse = New(IRCResponseERR_ALREADYREGISTERED)();
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_BADCHANNELKEY:
        {
            IRCResponseERR_BADCHANNELKEY* dynamicResponse = New(IRCResponseERR_BADCHANNELKEY)();
            if (dynamicResponse)
            {
                dynamicResponse->SetChannel(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_BANNEDFROMCHAN:
        {
            IRCResponseERR_BANNEDFROMCHAN* dynamicResponse = New(IRCResponseERR_BANNEDFROMCHAN)();
            if (dynamicResponse)
            {
                dynamicResponse->SetChannel(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_CANNOTSENDTOCHAN:
        {
            IRCResponseERR_CANNOTSENDTOCHAN* dynamicResponse = New(IRCResponseERR_CANNOTSENDTOCHAN)();
            if (dynamicResponse)
            {
                dynamicResponse->SetChannelName(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_CANTKILLSERVER:
        {
            IRCResponseERR_CANTKILLSERVER* dynamicResponse = New(IRCResponseERR_CANTKILLSERVER)();
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_CHANNELISFULL:
        {
            IRCResponseERR_CHANNELISFULL* dynamicResponse = New(IRCResponseERR_CHANNELISFULL)();
            if (dynamicResponse)
            {
                dynamicResponse->SetChannel(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_CHANOPRIVSNEEDED:
        {
            IRCResponseERR_CHANOPRIVSNEEDED* dynamicResponse = New(IRCResponseERR_CHANOPRIVSNEEDED)();
            if (dynamicResponse)
            {
                dynamicResponse->SetChannel(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_ERRONEUSNICKNAME:
        {
            IRCResponseERR_ERRONEUSNICKNAME* dynamicResponse = New(IRCResponseERR_ERRONEUSNICKNAME)();
            if (dynamicResponse)
            {
                dynamicResponse->SetNick(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_INVITEONLYCHAN:
        {
            IRCResponseERR_INVITEONLYCHAN* dynamicResponse = New(IRCResponseERR_INVITEONLYCHAN)();
            if (dynamicResponse)
            {
                dynamicResponse->SetChannel(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_NEEDMOREPARAMS:
        {
            IRCResponseERR_NEEDMOREPARAMS* dynamicResponse = New(IRCResponseERR_NEEDMOREPARAMS)();
            if (dynamicResponse)
            {
                dynamicResponse->SetCommand(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_NICKNAMEINUSE:
        {
            IRCResponseERR_NICKNAMEINUSE* dynamicResponse = New(IRCResponseERR_NICKNAMEINUSE)();
            if (dynamicResponse)
            {
                dynamicResponse->SetNick(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_NICKCOLLISION:
        {
            IRCResponseERR_NICKCOLLISION* dynamicResponse = New(IRCResponseERR_NICKCOLLISION)();
            if (dynamicResponse)
            {
                dynamicResponse->SetNick(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_NOMOTD:
        {
            IRCResponseERR_NOMOTD* dynamicResponse = New(IRCResponseERR_NOMOTD)();
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_NONICKNAMEGIVEN:
        {
            IRCResponseERR_NONICKNAMEGIVEN* dynamicResponse = New(IRCResponseERR_NONICKNAMEGIVEN)();
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_NOOPERHOST:
        {
            IRCResponseERR_NOOPERHOST* dynamicResponse = New(IRCResponseERR_NOOPERHOST)();
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_NOPRIVILEGES:
        {
            IRCResponseERR_NOPRIVILEGES* dynamicResponse = New(IRCResponseERR_NOPRIVILEGES)();
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_NORECIPIENT:
        {
            IRCResponseERR_NORECIPIENT* dynamicResponse = New(IRCResponseERR_NORECIPIENT)();
            if (dynamicResponse)
            {
                dynamicResponse->SetCommand(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_NOSUCHCHANNEL:
        {
            IRCResponseERR_NOSUCHCHANNEL* dynamicResponse = New(IRCResponseERR_NOSUCHCHANNEL)();
            if (dynamicResponse)
            {
                dynamicResponse->SetChannelName(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_NOSUCHNICK:
        {
            IRCResponseERR_NOSUCHNICK* dynamicResponse = New(IRCResponseERR_NOSUCHNICK)();
            if (dynamicResponse)
            {
                dynamicResponse->SetNickname(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_NOSUCHSERVER:
        {
            IRCResponseERR_NOSUCHSERVER* dynamicResponse = New(IRCResponseERR_NOSUCHSERVER)();
            if (dynamicResponse)
            {
                dynamicResponse->SetServerName(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_NOTEXTTOSEND:
        {
            IRCResponseERR_NOTEXTTOSEND* dynamicResponse = New(IRCResponseERR_NOTEXTTOSEND)();
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_NOTONCHANNEL:
        {
            IRCResponseERR_NOTONCHANNEL* dynamicResponse = New(IRCResponseERR_NOTONCHANNEL)();
            if (dynamicResponse)
            {
                dynamicResponse->SetChannel(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_NOTOPLEVEL:
        {
            IRCResponseERR_NOTOPLEVEL* dynamicResponse = New(IRCResponseERR_NOTOPLEVEL)();
            if (dynamicResponse)
            {
                dynamicResponse->SetMask(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_NOTREGISTERED:
        {
            IRCResponseERR_NOTREGISTERED* dynamicResponse = New(IRCResponseERR_NOTREGISTERED)();
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_PASSWDMISMATCH:
        {
            IRCResponseERR_PASSWDMISMATCH* dynamicResponse = New(IRCResponseERR_PASSWDMISMATCH)();
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_TOOMANYCHANNELS:
        {
            IRCResponseERR_TOOMANYCHANNELS* dynamicResponse = New(IRCResponseERR_TOOMANYCHANNELS)();
            if (dynamicResponse)
            {
                dynamicResponse->SetChannelName(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_TOOMANYTARGETS:
        {
            IRCResponseERR_TOOMANYTARGETS* dynamicResponse = New(IRCResponseERR_TOOMANYTARGETS)();
            if (dynamicResponse)
            {
                dynamicResponse->SetTarget(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_UNKNOWNCOMMAND:
        {
            IRCResponseERR_UNKNOWNCOMMAND* dynamicResponse = New(IRCResponseERR_UNKNOWNCOMMAND)();
            if (dynamicResponse)
            {
                dynamicResponse->SetCommand(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_USERONCHANNEL:
        {
            IRCResponseERR_USERONCHANNEL* dynamicResponse = New(IRCResponseERR_USERONCHANNEL)();
            if (dynamicResponse)
            {
                dynamicResponse->SetUser(arg1);
                dynamicResponse->SetChannel(arg2);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_ERR_WILDTOPLEVEL:
        {
            IRCResponseERR_WILDTOPLEVEL* dynamicResponse = New(IRCResponseERR_WILDTOPLEVEL)();
            if (dynamicResponse)
            {
                dynamicResponse->SetMask(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_RPL_AWAY:
        {
            IRCResponseRPL_AWAY* dynamicResponse = New(IRCResponseRPL_AWAY)();
            if (dynamicResponse)
            {
                dynamicResponse->SetNick(arg1);
                dynamicResponse->SetAwayMessage(arg2);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_RPL_ENDOFMOTD:
        {
            IRCResponseRPL_ENDOFMOTD* dynamicResponse = New(IRCResponseRPL_ENDOFMOTD)();
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_RPL_ENDOFNAMES:
        {
            IRCResponseRPL_ENDOFNAMES* dynamicResponse = New(IRCResponseRPL_ENDOFNAMES)();
            if (dynamicResponse)
            {
                dynamicResponse->SetChannel(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_RPL_INVITING:
        {
            IRCResponseRPL_INVITING* dynamicResponse = New(IRCResponseRPL_INVITING)();
            if (dynamicResponse)
            {
                dynamicResponse->SetChannel(arg1);
                dynamicResponse->SetNick(arg2);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_RPL_LIST:
        {
            IRCResponseRPL_LIST* dynamicResponse = New(IRCResponseRPL_LIST)();
            if (dynamicResponse)
            {
                dynamicResponse->SetChannel(arg1);
                dynamicResponse->SetNbVisible(arg2);
                dynamicResponse->SetTopic(arg3);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_RPL_LISTEND:
        {
            IRCResponseRPL_LISTEND* dynamicResponse = New(IRCResponseRPL_LISTEND)();
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_RPL_LISTSTART:
        {
            IRCResponseRPL_LISTSTART* dynamicResponse = New(IRCResponseRPL_LISTSTART)();
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_RPL_MOTD:
        {
            IRCResponseRPL_MOTD* dynamicResponse = New(IRCResponseRPL_MOTD)();
            if (dynamicResponse)
            {
                dynamicResponse->SetText(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_RPL_MOTDSTART:
        {
            IRCResponseRPL_MOTDSTART* dynamicResponse = New(IRCResponseRPL_MOTDSTART)();
            if (dynamicResponse)
            {
                dynamicResponse->SetServer(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_RPL_NAMREPLY:
        {
            IRCResponseRPL_NAMREPLY* dynamicResponse = New(IRCResponseRPL_NAMREPLY)();
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_RPL_NOTOPIC:
        {
            IRCResponseRPL_NOTOPIC* dynamicResponse = New(IRCResponseRPL_NOTOPIC)();
            if (dynamicResponse)
            {
                dynamicResponse->SetChannel(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_RPL_TOPIC:
        {
            IRCResponseRPL_TOPIC* dynamicResponse = New(IRCResponseRPL_TOPIC)();
            if (dynamicResponse)
            {
                dynamicResponse->SetChannel(arg1);
                dynamicResponse->SetTopic(arg2);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_RPL_UMODEIS:
        {
            IRCResponseRPL_UMODEIS* dynamicResponse = New(IRCResponseRPL_UMODEIS)();
            if (dynamicResponse)
            {
                dynamicResponse->SetUserModeString(arg1);
            }
            response = dynamicResponse;
            break;
        }
        case Enum_IRCResponses_RPL_YOUREOPER:
        {
            IRCResponseRPL_YOUREOPER* dynamicResponse = New(IRCResponseRPL_YOUREOPER)();
            response = dynamicResponse;
            break;
        }
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
