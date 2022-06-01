#include "main/precomp.h"

#include "irccommands/ircpartcommand.h"

#include "ircchannel/ircchannel.h"
#include "ircclient/ircclient.h"
#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
#include "ircresponses/ircresponseshelper.h"
#include "managers/ircclientsmanager.h"
#include "managers/ircchannelsmanager.h"
#include "parsing/ircparsinghelper.h"


namespace ircserv
{

IRCPartCommand::IRCPartCommand() : IRCCommand(Enum_IRCCommands_Part)
{
    Initialize();
}

void IRCPartCommand::Initialize(void)
{
}

IRCPartCommand::~IRCPartCommand()
{
    Shutdown();
}

void IRCPartCommand::Shutdown(void)
{
}

bool IRCPartCommand::ProcessCommand(IRCSocket *socket)
{
    if (!IRCCommandsHelper::IsRegistered(socket))
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOTREGISTERED);
        return false;
    }

    if (ValidateArgs(socket))
    {
        for (size_t i = 0; i < GetChannels().size(); ++i)
        {
            IRCClient *client = GetIRCClientsManager().FindClient(socket);
            IRCChannel *channel = GetIRCChannelsManager().FindChannel(GetChannels()[i]);
            if (!channel || !IRCCommandsHelper::IsInContainer(channel->GetClients(), client))
            {
                IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOTONCHANNEL, GetChannels()[i]);
                continue;
            }

            std::string message = ":" + client->GetNickname() + "!" + client->GetUsername() + "@" + client->GetHostname() + " " + EnumString<Enum_IRCCommands>::From(GetCommandEnum()) + " " +  GetChannels()[i] + "\n";
            if (IRCCommandsHelper::IsClientVisible(client))
            {
                IRCResponsesHelper::SendMessageToAllChannelNames(GetChannels()[i], message);
            }

            channel->RemoveClient(client);
            channel->RemoveOper(client);
            if (channel->GetOpers().empty())
            {
                if (channel->GetClients().empty())
                {
                    GetIRCChannelsManager().EraseChannel(GetChannels()[i]);
                }
                else
                {
                    channel->AddOper(*(channel->GetClients().begin()));
                }
            }
        }
        return true;
    }
    return false;
}

bool IRCPartCommand::ValidateArgs(IRCSocket *socket)
{
    std::vector<std::string> channels;
    if (GetArgs().empty())
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NEEDMOREPARAMS, EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
        return false;
    }
    else
    {
        std::vector<std::string> channels = IRCParsingHelper::Split(GetArgs()[0], ",");

        for (size_t i = 0; i < channels.size(); )
        {
            if (!IRCParsingHelper::IsChannel(channels[i]))
            {
                IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOSUCHCHANNEL, channels[i]);
                channels.erase(channels.begin() + i);
            }
            else
            {
                ++i;
            }
        }
        SetChannels(channels);
    }
    return true;
}

}
