#include "main/precomp.h"

#include "irccommands/irctopiccommand.h"

#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
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
    if (!IRCCommandsHelper::IsRegistered(socket))
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOTREGISTERED);
        return false;
    }

    if (ValidateArgs(socket))
    {
        IRCClient *client = GetIRCClientsManager().FindClient(socket);
        IRCChannel *channel = GetIRCChannelsManager().FindChannel(GetChannel());
        if (!channel || !IRCCommandsHelper::IsInContainer(channel->GetClients(), client))
        {
            IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOTONCHANNEL, GetChannel());
            return false;
        }
        if (!GetTopic().empty())
        {
            if (channel->GetModes() & TOPICSET)
            {
                if (!IRCCommandsHelper::IsInContainer(channel->GetOpers(), client))
                {
                    IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_CHANOPRIVSNEEDED, GetChannel());
                    return false;
                }
            }
            channel->SetTopic(GetTopic());
            if (client)
            {
                std::string message = ":" + client->GetNickname() + "!" + client->GetUsername() + "@" + client->GetHostname() + " " + EnumString<Enum_IRCCommands>::From(GetCommandEnum()) + " :" + GetTopic() + "\n";
                if (IRCCommandsHelper::IsClientVisible(client))
                {
                    IRCResponsesHelper::SendMessageToAllChannelNames(GetChannel(), message);
                }
            }
        }
        else
        {
            IRCResponsesHelper::SendTopic(socket, GetChannel(), channel->GetTopic());
        }
        
        return true;
    }
    return false;
}

bool IRCTopicCommand::ValidateArgs(IRCSocket *socket)
{
    std::vector<std::string> channels;
    if (GetArgs().empty())
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NEEDMOREPARAMS, EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
        return false;
    }
    else
    {
        SetChannel(GetArgs()[0]);
        if (GetArgs().size() > 1)
        {
            SetTopic(GetArgs()[1]);
        }
    }
    return true;
}

}
