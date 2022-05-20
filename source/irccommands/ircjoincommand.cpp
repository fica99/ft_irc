#include "main/precomp.h"

#include "irccommands/ircjoincommand.h"
#include "irccommands/irccommands.h"

#include "parsing/ircparsinghelper.h"
#include "ircresponses/ircresponseerr_bannedfromchan.h"
#include "ircresponses/ircresponseerr_channelisfull.h"
#include "ircresponses/ircresponseerr_inviteonlychan.h"
#include "ircresponses/ircresponseerr_needmoreparams.h"
#include "ircresponses/ircresponseerr_toomanychannels.h"
#include "ircresponses/ircresponserpl_topic.h"
#include "ircresponses/ircresponsesfactory.h"

namespace ircserv
{

IRCJoinCommand::IRCJoinCommand() : IRCCommand(Enum_IRCCommands_Join)
{
    Initialize();
}

void IRCJoinCommand::Initialize(void)
{
}

IRCJoinCommand::~IRCJoinCommand()
{
    Shutdown();
}

void IRCJoinCommand::Shutdown(void)
{
}

bool IRCJoinCommand::ProcessCommand(void)
{
    // if (ValidateArgs(serv))
    // {
    //     for (size_t i = 0; i < GetChannels().size(); ++i)
    //     {

    //         IRCResponse* response = GetIRCResponsesFactory().CreateResponse(serv->joinCommand(GetChannels()[i]));

    //         if (response)
    //         {
    //             IRCResponseERR_TOOMANYCHANNELS *responseTooManyChannels = dynamic_cast<IRCResponseERR_TOOMANYCHANNELS*>(response);
    //             IRCResponseERR_INVITEONLYCHAN *responseInviteOnlyChannel = dynamic_cast<IRCResponseERR_INVITEONLYCHAN*>(response);
    //             IRCResponseERR_CHANNELISFULL *responseChannelIsFull = dynamic_cast<IRCResponseERR_CHANNELISFULL*>(response);
    //             IRCResponseERR_BANNEDFROMCHAN *responseBannedFromChan = dynamic_cast<IRCResponseERR_BANNEDFROMCHAN*>(response);
    //             IRCResponseRPL_TOPIC *responseTopic = dynamic_cast<IRCResponseRPL_TOPIC*>(response);

    //             if (responseTooManyChannels != NULL)
    //             {
    //                 responseTooManyChannels->SetChannelName(GetChannels()[i]);
    //                 serv->sendResponse(responseTooManyChannels->GetResponse());
    //             }
    //             else if (responseInviteOnlyChannel != NULL)
    //             {
    //                 responseInviteOnlyChannel->SetChannel(GetChannels()[i]);
    //                 serv->sendResponse(responseInviteOnlyChannel->GetResponse());
    //             }
    //             else if (responseChannelIsFull != NULL)
    //             {
    //                 responseChannelIsFull->SetChannel(GetChannels()[i]);
    //                 serv->sendResponse(responseChannelIsFull->GetResponse());
    //             }
    //             else if (responseBannedFromChan != NULL)
    //             {
    //                 responseBannedFromChan->SetChannel(GetChannels()[i]);
    //                 serv->sendResponse(responseBannedFromChan->GetResponse());
    //             }
    //             else if (responseTopic != NULL)
    //             {
    //                 responseTopic->SetChannel(GetChannels()[i]);
    //                 responseTopic->SetTopic(serv->getTopic(GetChannels()[i]));
    //                 serv->sendResponse(responseTopic->GetResponse());
    //             }

    //             GetIRCResponsesFactory().DestroyResponse(response);
    //         }
    //     }
    //     return true;
    // }
    return false;
}

bool IRCJoinCommand::ValidateArgs(void)
{
    // if (m_Args.empty())
    // {
    //     IRCResponseERR_NEEDMOREPARAMS* response = dynamic_cast<IRCResponseERR_NEEDMOREPARAMS*>(
    //         GetIRCResponsesFactory().CreateResponse(Enum_IRCResponses_ERR_NEEDMOREPARAMS)
    //     );
    //     if (response != NULL)
    //     {
    //         response->SetCommand(EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
    //         serv->sendResponse(response->GetResponse());
    //     }
    //     GetIRCResponsesFactory().DestroyResponse(response);
    //     return false;
    // }
    // else
    // {
    //     if (!IRCParsingHelper::IsChannels(m_Args[0]))
    //     {
    //         return false;
    //     }
    //     SetChannels(IRCParsingHelper::Split(m_Args[0], ","));
    //     if (m_Args.size() > 1)
    //     {
    //         SetKeys(IRCParsingHelper::Split(m_Args[1], ","));
    //     }
    // }
    return true;
}


}
