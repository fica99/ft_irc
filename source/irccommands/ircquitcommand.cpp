#include "main/precomp.h"

#include "irccommands/ircquitcommand.h"

#include "ircclient/ircclient.h"
#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
#include "ircserver/ircserver.h"
#include "ircserver/ircsocket.h"
#include "managers/ircclientsmanager.h"
#include "managers/ircchannelsmanager.h"
#include "ircresponses/ircresponseshelper.h"

namespace ircserv
{

IRCQuitCommand::IRCQuitCommand() : IRCCommand(Enum_IRCCommands_Quit)
{
    Initialize();
}

void IRCQuitCommand::Initialize(void)
{
}

IRCQuitCommand::~IRCQuitCommand()
{
    Shutdown();
}

void IRCQuitCommand::Shutdown(void)
{
}

bool IRCQuitCommand::ProcessCommand(IRCSocket *socket)
{
    if (!GetArgs().empty())
    {
        SetQuitMessage(GetArgs()[0]);
    }
    IRCClient *client = GetIRCClientsManager().FindClient(socket);
    if (client)
    {
        std::string message = ":" + client->GetNickname() + "!" + client->GetUsername() + "@" + client->GetHostname() + " " + EnumString<Enum_IRCCommands>::From(GetCommandEnum()) + " :" + GetQuitMessage() + "\n";
        for (std::unordered_set<IRCChannel*>::iterator it = client->GetJoinedChannels().begin(); it != client->GetJoinedChannels().end(); it = client->GetJoinedChannels().begin())
        {
            IRCChannel *channel = *it;
            if (channel)
            {
                if (IRCCommandsHelper::IsClientVisible(client))
                {
                    IRCResponsesHelper::SendMessageToAllChannelNames(channel->GetName(), message);
                }

                channel->RemoveClient(client);
                channel->RemoveOper(client);
                if (channel->GetOpers().empty())
                {
                    if (channel->GetClients().empty())
                    {
                        GetIRCChannelsManager().EraseChannel(channel->GetName());
                    }
                    else
                    {
                        channel->AddOper(*(channel->GetClients().begin()));
                    }
                }
            }
        }

    }
    GetIRCClientsManager().EraseClient(socket);
    GetIRCServer().CloseConnection(socket);
    return true;
}

}
