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


}
