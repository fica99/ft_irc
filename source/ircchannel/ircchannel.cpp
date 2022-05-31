#include "main/precomp.h"

#include "ircchannel/ircchannel.h"

#define MAX_NB_USERS_IN_CHANNEL 40

namespace ircserv
{

IRCChannel::IRCChannel()
{
    Initialize();
}

void IRCChannel::Initialize(void)
{
    m_Modes = 0;
    m_MaxUsersInChannel = MAX_NB_USERS_IN_CHANNEL;
}

IRCChannel::~IRCChannel()
{
    Shutdown();
}

void IRCChannel::Shutdown(void)
{
}

bool IRCChannel::AddClient(IRCClient* client)
{
    bool isInserted = m_Clients.insert(client).second;
    if (isInserted)
    {
        if (client)
        {
            client->JoinChannel(this);
        }
    }
    return isInserted;
}

void IRCChannel::RemoveClient(IRCClient* client)
{
    std::unordered_set<IRCClient*>::iterator it = m_Clients.find(client);
    if (it != m_Clients.end())
    {
        if (client)
        {
            client->LeaveChannel(this);
        }
        m_Clients.erase(it);
    }
}

void IRCChannel::RemoveOper(IRCClient* oper)
{
    std::unordered_set<IRCClient*>::iterator it = m_Opers.find(oper);
    if (it != m_Opers.end())
    {
        m_Opers.erase(it);
    }
}

void IRCChannel::UnbanNick(const std::string& nick)
{
    std::unordered_set<std::string>::iterator it = m_BannedNicks.find(nick);
    if (it != m_BannedNicks.end())
    {
        m_BannedNicks.erase(it);
    }
}

}
