#include "main/precomp.h"

#include "managers/ircclientsmanager.h"

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
}

IRCClientsManager::~IRCClientsManager()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void IRCClientsManager::Shutdown(void)
{
    for (std::unordered_map<IRCSocket*, IRCClient*>::iterator it = m_SocketClientsMap.begin(); it != m_SocketClientsMap.end(); )
    {
        Delete(it->second);
        it = m_SocketClientsMap.erase(it);
    }
    m_SocketClientsMap.clear();
}

IRCClient *IRCClientsManager::FindOrCreateClient(IRCSocket *socket)
{
    IRCClient *client = FindClient(socket);

    if (client == NULL)
    {
        client = New(IRCClient);
        m_SocketClientsMap[socket] = client;
        IRC_LOGD("%s", "Client created");
    }
    return client;
}

IRCClient *IRCClientsManager::FindClient(IRCSocket *socket)
{
    IRCClient *client = NULL;
    std::unordered_map<IRCSocket*, IRCClient*>::iterator it = m_SocketClientsMap.find(socket);
    
    if (it != m_SocketClientsMap.end())
    {
        client = it->second;
    }
    return client;
}

IRCClient *IRCClientsManager::FindClientByNickname(const std::string& nickname) const
{
    for ( std::unordered_map<IRCSocket*, IRCClient*>::const_iterator it = m_SocketClientsMap.begin(); it != m_SocketClientsMap.end(); ++it)
    {
        if (it->second->GetNickname() == nickname)
        {
            return it->second;
        }
    }
    return NULL;
}

void IRCClientsManager::EraseClient(IRCSocket *socket)
{
    std::unordered_map<IRCSocket*, IRCClient*>::iterator it = m_SocketClientsMap.find(socket);
    if (it != m_SocketClientsMap.end())
    {
        Delete(it->second);
        m_SocketClientsMap.erase(it);
        IRC_LOGD("%s", "Client erased");
    }
}

void IRCClientsManager::AddOper(const std::string& user, const std::string& password)
{
    m_OpersMap[user] = password;
}

bool IRCClientsManager::IsRegistered(IRCSocket *socket)
{
    IRCClient *client = FindClient(socket);
    if (client != NULL)
    {
        return client->GetIsRegistered();
    }
    return false;
}

bool IRCClientsManager::IsOper(const std::string& user, const std::string& password)
{
     std::unordered_map<std::string, std::string>::iterator it = m_OpersMap.find(user);
    if (it != m_OpersMap.end())
    {
        if (password == it->second)
        {
            return true;
        }
    }
    return false;
}


}
