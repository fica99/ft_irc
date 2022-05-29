#include "main/precomp.h"

#include "ircchannel/ircchannel.h"

#include "ircclient/ircclient.h"
#include "managers/ircclientsmanager.h"

namespace ircserv
{

IRCChannel::IRCChannel()
{
    Initialize();
}

void IRCChannel::Initialize(void)
{
    m_IsInviteOnly = false;
}

IRCChannel::~IRCChannel()
{
    Shutdown();
}

void IRCChannel::Shutdown(void)
{
}

bool IRCChannel::AddUser(IRCSocket* user)
{
    bool isInserted = m_Users.insert(user).second;
    if (isInserted)
    {
        IRCClient *client = GetIRCClientsManager().FindClient(user);
        if (client)
        {
            client->JoinChannel();
        }
    }
    return isInserted;
}

void IRCChannel::RemoveUser(IRCSocket* user)
{
    m_Users.erase(m_Users.find(user));
    IRCClient *client = GetIRCClientsManager().FindClient(user);
    if (client)
    {
        client->LeaveChannel();
    }
}


}
