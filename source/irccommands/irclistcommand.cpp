#include "main/precomp.h"

#include "irccommands/irclistcommand.h"

#include "ircchannel/ircchannel.h"
#include "ircclient/ircclient.h"
#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
#include "ircresponses/ircresponseshelper.h"
#include "managers/ircchannelsmanager.h"
#include "managers/ircclientsmanager.h"
#include "parsing/ircparsinghelper.h"

namespace ircserv
{

IRCListCommand::IRCListCommand() : IRCCommand(Enum_IRCCommands_List)
{
    Initialize();
}

void IRCListCommand::Initialize(void)
{
}

IRCListCommand::~IRCListCommand()
{
    Shutdown();
}

void IRCListCommand::Shutdown(void)
{
}

bool IRCListCommand::ProcessCommand(IRCSocket *socket)
{
    if (!IRCCommandsHelper::IsRegistered(socket))
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOTREGISTERED);
        return false;
    }

    if (ValidateArgs(socket))
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_RPL_LISTSTART);
        if (GetChannels().empty())
        {
            for (std::unordered_map<std::string, IRCChannel*>::const_iterator it = GetIRCChannelsManager().GetChannelsMap().begin(); it != GetIRCChannelsManager().GetChannelsMap().end(); ++it)
            {
                PrintChannelStatus(socket, it->first);
            }
        }
        else
        {
            for (size_t i = 0; i < GetChannels().size(); ++i)
            {
                PrintChannelStatus(socket, GetChannels()[i]);
            }
        }
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_RPL_LISTEND);
        return true;
    }
    return false;
}

bool IRCListCommand::ValidateArgs(IRCSocket *socket)
{
    (void)(socket);
    if (!GetArgs().empty())
    {
        SetChannels(IRCParsingHelper::Split(GetArgs()[0], ","));
    }
    return true;
}

void IRCListCommand::PrintChannelStatus(IRCSocket *socket, const std::string& channelName) const
{
    IRCChannel *channel = GetIRCChannelsManager().FindChannel(channelName);
    if (channel)
    {
        IRCClient *client = GetIRCClientsManager().FindClient(socket);
        std::string chanName = channelName;
        size_t nbVisibleUsers = 0;
        std::string topic = channel->GetTopic();
        if (channel->GetModes() & PRIVATE)
        {
            if (!IRCCommandsHelper::IsInContainer(channel->GetClients(), client))
            {
                chanName = "*";
                topic = "";
            }
        }
        if (channel->GetModes() & SECRET)
        {
            if (!IRCCommandsHelper::IsInContainer(channel->GetClients(), client))
            {
                return;
            }
        }
        nbVisibleUsers = IRCCommandsHelper::GetNbVisibleClients(channel->GetClients());
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_RPL_LIST, chanName, std::to_string(nbVisibleUsers), topic);
    }
}

}
