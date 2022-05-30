#include "main/precomp.h"

#include "irccommands/irccommandshelper.h"

#include "ircclient/ircclient.h"
#include "managers/ircclientsmanager.h"

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


}
