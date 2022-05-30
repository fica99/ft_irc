#include "main/precomp.h"

#include "irccommands/irccommandshelper.h"

#include "ircclient/ircclient.h"
#include "managers/ircclientsmanager.h"
#include "managers/ircchannelsmanager.h"

namespace ircserv
{

bool IRCCommandsHelper::IsRegistered(IRCSocket *socket)
{
    IRCClientsManager& manager = GetIRCClientsManager();

    std::unordered_map<IRCSocket*, IRCClient*>::const_iterator it = manager.GetSocketsClientsMap().find(socket);
    if (it == manager.GetSocketsClientsMap().end())
    {
        return false;
    }
    IRCClient *client = it->second;
    if (client)
    {
        return client->GetIsRegistered();
    }

    return false;
}

bool IRCCommandsHelper::IsBannedByChannel(IRCClient *client, IRCChannel *channel)
{
    if (channel)
    {
        std::unordered_set<IRCClient*>::const_iterator it = channel->GetBanned().find(client);
        if (it != channel->GetBanned().end())
        {
            return true;
        }
    }
    return false;
}

void IRCCommandsHelper::EraseClientFromChannel(IRCClient *client, IRCChannel *channel)
{
    if (channel)
    {
        channel->RemoveClient(client);
        if (channel->GetClients().empty())
        {
            GetIRCChannelsManager().EraseChannel(channel->GetName());
        }
    }
}


}
