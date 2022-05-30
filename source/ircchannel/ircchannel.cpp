#include "main/precomp.h"

#include "ircchannel/ircchannel.h"

namespace ircserv
{

IRCChannel::IRCChannel()
{
    Initialize();
}

void IRCChannel::Initialize(void)
{
    m_Modes = 0;
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

void IRCChannel::AddOper(IRCClient* oper)
{
    m_Opers.insert(oper);
}

void IRCChannel::RemoveOper(IRCClient* oper)
{
    std::unordered_set<IRCClient*>::iterator it = m_Opers.find(oper);
    if (it != m_Opers.end())
    {
        m_Opers.erase(it);
    }
}

void IRCChannel::BanClient(IRCClient* client)
{
    m_Banned.insert(client);
}

void IRCChannel::UnbanClient(IRCClient* client)
{
    std::unordered_set<IRCClient*>::iterator it = m_Banned.find(client);
    if (it != m_Banned.end())
    {
        m_Banned.erase(it);
    }
}

}
