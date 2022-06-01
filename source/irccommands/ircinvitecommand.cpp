#include "main/precomp.h"

#include "irccommands/ircinvitecommand.h"

#include "ircchannel/ircchannel.h"
#include "ircclient/ircclient.h"
#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
#include "ircresponses/ircresponses.h"
#include "ircresponses/ircresponseshelper.h"
#include "managers/ircchannelsmanager.h"
#include "managers/ircclientsmanager.h"

namespace ircserv
{

IRCInviteCommand::IRCInviteCommand() : IRCCommand(Enum_IRCCommands_Invite)
{
    Initialize();
}

void IRCInviteCommand::Initialize(void)
{
}

IRCInviteCommand::~IRCInviteCommand()
{
    Shutdown();
}

void IRCInviteCommand::Shutdown(void)
{
}

bool IRCInviteCommand::ProcessCommand(IRCSocket *socket)
{
    if (!IRCCommandsHelper::IsRegistered(socket))
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOTREGISTERED);
        return false;
    }

    if (ValidateArgs(socket))
    {
        IRCClient *client = GetIRCClientsManager().FindClient(socket);
        IRCClient *invitedClient = GetIRCClientsManager().FindClientByNickname(GetNickname());
        IRCChannel *channel = GetIRCChannelsManager().FindChannel(GetChannel());
        if (!invitedClient)
        {
            IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOSUCHNICK, GetNickname());
            return false;
        }

        if (!channel || !IRCCommandsHelper::IsInContainer(channel->GetClients(), client))
        {
            IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOTONCHANNEL, GetChannel());
            return false;
        }

        if (IRCCommandsHelper::IsInContainer(channel->GetClients(), invitedClient))
        {
            IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_USERONCHANNEL, client->GetNickname(), channel->GetName());
            return false;
        }

        if (channel->GetModes() & INVITEONLY)
        {
            if (!IRCCommandsHelper::IsInContainer(channel->GetOpers(), client))
            {
                IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_CHANOPRIVSNEEDED, channel->GetName());
                return false;
            }
        }

        std::string message = ":" + client->GetNickname() + "!" + client->GetUsername() + "@" + client->GetHostname() + " " + EnumString<Enum_IRCCommands>::From(GetCommandEnum()) + " " + GetNickname() + " :" + GetChannel() + "\n";
        IRCSocket *invitedSocket = GetIRCClientsManager().FindSocketByClient(invitedClient);
        if (invitedSocket)
        {
            IRCResponsesHelper::Send(invitedSocket, message);
        }
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_RPL_INVITING, GetChannel(), GetNickname());
        return true;
    }
    return false;
}

bool IRCInviteCommand::ValidateArgs(IRCSocket *socket)
{
    if (GetArgs().size() < 2)
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NEEDMOREPARAMS, EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
        return false;
    }
    else
    {
        SetNickname(GetArgs()[0]);
        SetChannel(GetArgs()[1]);
    }
    return true;
}
}
