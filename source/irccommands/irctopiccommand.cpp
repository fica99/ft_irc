#include "main/precomp.h"

#include "irccommands/irctopiccommand.h"

#include "irccommands/irccommands.h"
#include "ircresponses/ircresponseshelper.h"
#include "ircresponses/ircresponses.h"
#include "managers/ircclientsmanager.h"
#include "managers/ircchannelsmanager.h"


namespace ircserv
{

IRCTopicCommand::IRCTopicCommand() : IRCCommand(Enum_IRCCommands_Topic)
{
    Initialize();
}

void IRCTopicCommand::Initialize(void)
{
}

IRCTopicCommand::~IRCTopicCommand()
{
    Shutdown();
}

void IRCTopicCommand::Shutdown(void)
{
}

bool IRCTopicCommand::ProcessCommand(IRCSocket *socket)
{
    // if (!GetIRCClientsManager().IsRegistered(socket))
    // {
    //     IRCResponsesHelper::SendResponseWithoutParams(socket, Enum_IRCResponses_ERR_NOTREGISTERED);
    //     return false;
    // }

    // if (ValidateArgs(socket))
    // {
    //     Enum_IRCResponses responseEnum = GetIRCChannelsManager().Topic(socket, GetChannel(), GetTopic());
    //     if (responseEnum == Enum_IRCResponses_RPL_TOPIC)
    //     {
    //         IRCChannel *channel = GetIRCChannelsManager().FindChannel(GetChannel());
    //         IRCResponsesHelper::SendResponseWithTopic(socket, GetChannel(), channel ? channel->GetTopic() : "");
    //     }
    //     else if (responseEnum == Enum_IRCResponses_ERR_NOTONCHANNEL)
    //     {
    //         IRCResponsesHelper::SendResponseWithServerName(socket, responseEnum, GetChannel());
    //     }
    //     return true;
    // }
    return false;
}

bool IRCTopicCommand::ValidateArgs(IRCSocket *socket)
{
    // std::vector<std::string> channels;
    // if (GetArgs().empty())
    // {
    //     IRCResponsesHelper::SendResponseWithoutParams(socket, Enum_IRCResponses_ERR_NEEDMOREPARAMS);
    //     return false;
    // }
    // else
    // {
    //     SetChannel(GetArgs()[0]);
    //     if (GetArgs().size() > 1)
    //     {
    //         SetTopic(GetArgs()[1]);
    //     }
    // }
    return true;
}

}
