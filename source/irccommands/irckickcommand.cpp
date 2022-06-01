#include "main/precomp.h"

#include "irccommands/irckickcommand.h"

#include "ircclient/ircclient.h"
#include "ircchannel/ircchannel.h"
#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
#include "ircresponses/ircresponseshelper.h"
#include "parsing/ircparsinghelper.h"
#include "managers/ircchannelsmanager.h"
#include "managers/ircclientsmanager.h"

namespace ircserv
{

IRCKickCommand::IRCKickCommand() : IRCCommand(Enum_IRCCommands_Kick)
{
    Initialize();
}

void IRCKickCommand::Initialize(void)
{
}

IRCKickCommand::~IRCKickCommand()
{
    Shutdown();
}

void IRCKickCommand::Shutdown(void)
{
}

bool IRCKickCommand::ProcessCommand(IRCSocket *socket)
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
   
        if (!IRCCommandsHelper::IsInContainer(channel->GetOpers(), client))
        {
            IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_CHANOPRIVSNEEDED, channel->GetName());
            return false;
        }
        
        std::string message = ":" + client->GetNickname() + "!" + client->GetUsername() + "@" + client->GetHostname() + " " + EnumString<Enum_IRCCommands>::From(GetCommandEnum()) + " " +  GetChannel() + " " + GetUser() + " :" + GetComment() + "\n";
        if (IRCCommandsHelper::IsClientVisible(client))
        {
            IRCResponsesHelper::SendMessageToAllChannelNames(GetChannel(), message);
        }

        channel->RemoveClient(client);
        channel->RemoveOper(client);

        return true;
    }
    return false;
}

bool IRCKickCommand::ValidateArgs(IRCSocket *socket)
{
    if (GetArgs().size() < 2)
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NEEDMOREPARAMS, EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
        return false;
    }
    else
    {
        if (!IRCParsingHelper::IsChannel(GetArgs()[0]))
        {
            IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOSUCHCHANNEL, GetArgs()[0]);
            return false;
        }
        SetChannel(GetArgs()[0]);
        SetUser(GetArgs()[1]);
        if (GetArgs().size() > 2)
        {
            SetComment(GetArgs()[2]);
        }
    }
    return true;
}
}
