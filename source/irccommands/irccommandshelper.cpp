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

bool IRCCommandsHelper::IsChannelVisible(IRCChannel *channel)
{
    if (channel)
    {
        if (channel->GetModes() & PRIVATE || channel->GetModes() & SECRET)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    return false;
}

bool IRCCommandsHelper::IsAnyChannelVisiable(const std::unordered_set<IRCChannel*>& channels)
{
    for (std::unordered_set<IRCChannel*>::const_iterator it = channels.begin(); it != channels.end(); ++it )
    {
        if (IsChannelVisible(*it))
        {
            return true;
        }
    }
    return false;
}

bool IRCCommandsHelper::IsClientVisible(IRCClient *client)
{
    if (client)
    {
        return (!(client->GetModes() & INVISIBLE));
    }
    return false;
}

}
