#include "main/precomp.h"

#include "managers/ircclientsmanager.h"

#include "ircchannel/ircchannel.h"
#include "utils/memory.h"

namespace ircserv
{

IMPLEMENT_SIMPLE_SINGLETON(IRCClientsManager);

IRCClientsManager::IRCClientsManager()
{
    IMPLEMENT_SIMPLE_SINGLETON_CONSTRUCTOR();

    Initialize();
}

void IRCClientsManager::Initialize(void)
{
    m_OpersMap["aashara"] = "070599";
}

IRCClientsManager::~IRCClientsManager()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void IRCClientsManager::Shutdown(void)
{
    for (std::unordered_map<IRCSocket*, IRCClient*>::iterator it = m_SocketsClientsMap.begin(); it != m_SocketsClientsMap.end(); )
    {
        EraseClient(it->first);
    }
    m_SocketsClientsMap.clear();
}

IRCClient *IRCClientsManager::CreateClient(IRCSocket *socket)
{
    IRCClient *client;

    client = New(IRCClient);
    if (client != NULL)
    {
        m_SocketsClientsMap[socket] = client;
        IRC_LOGD("%s", "Client created");
    }
    return client;
}

IRCClient *IRCClientsManager::FindClient(IRCSocket *socket) const
{
    IRCClient *client = NULL;
    std::unordered_map<IRCSocket*, IRCClient*>::const_iterator it = m_SocketsClientsMap.find(socket);
    
    if (it != m_SocketsClientsMap.end())
    {
        client = it->second;
    }
    return client;
}

IRCClient *IRCClientsManager::FindOrCreateClient(IRCSocket *socket)
{
    IRCClient *client = FindClient(socket);

    if (client == NULL)
    {
        client = CreateClient(socket);
    }
    return client;
}

IRCClient *IRCClientsManager::FindClientByNickname(const std::string& nickname) const
{
    for ( std::unordered_map<IRCSocket*, IRCClient*>::const_iterator it = m_SocketsClientsMap.begin(); it != m_SocketsClientsMap.end(); ++it)
    {
        if (it->second->GetNickname() == nickname)
        {
            return it->second;
        }
    }
    return NULL;
}

IRCSocket *IRCClientsManager::FindSocketByClient(IRCClient *client) const
{
    for ( std::unordered_map<IRCSocket*, IRCClient*>::const_iterator it = m_SocketsClientsMap.begin(); it != m_SocketsClientsMap.end(); ++it)
    {
        if (it->second == client)
        {
            return it->first;
        }
    }
    return NULL;
}

void IRCClientsManager::EraseClient(IRCSocket *socket)
{
    std::unordered_map<IRCSocket*, IRCClient*>::iterator it = m_SocketsClientsMap.find(socket);
    if (it != m_SocketsClientsMap.end())
    {
        IRCClient *client = it->second;
        if (client != NULL)
        {
            for (std::unordered_set<IRCChannel*>::const_iterator it = client->GetJoinedChannels().begin(); it != client->GetJoinedChannels().end(); ++it)
            {
                IRCChannel* channel = (*it);
                channel->RemoveClient(client);
            }
        }
        Delete(client);
        m_SocketsClientsMap.erase(it);
        IRC_LOGD("%s", "Client erased");
    }
}

}
