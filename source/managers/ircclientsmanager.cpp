#include "main/precomp.h"

#include "ircserver/ircserver.h"
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

void IRCClientsManager::Quit(IRCSocket *socket, const std::string& quitMessage)
{
    std::unordered_map<IRCSocket*, IRCClient*>::iterator it = m_SocketClientsMap.find(socket);
    if (it != m_SocketClientsMap.end())
    {
        Delete(it->second);
        m_SocketClientsMap.erase(it);
        GetIRCServer().CloseConnection(socket);
        IRC_LOGI("%s", "Client disconnected");
    }
}

bool IRCClientsManager::Pass(IRCSocket *socket, const std::string& password)
{
    IRCClient *client = FindOrCreateClient(socket);

    if (client->GetIsRegistered())
    {
        return false;
    }
    else
    {
        client->SetPassword(password);
    }
    return true;
}

Enum_IRCResponses IRCClientsManager::Nick(IRCSocket *socket, const std::string& nickname)
{
    if (FindClientByNickname(nickname) != NULL)
    {
        return Enum_IRCResponses_ERR_NICKNAMEINUSE;
    }
    IRCClient *client = FindOrCreateClient(socket);
    client->SetNickname(nickname);
    if (client->GetIsRegistered() == true)
    {
        if (client->GetPassword() != GetIRCServer().GetPassword())
        {
            Quit(socket, "");
        }
    }
    return Enum_IRCResponses_Unknown;
}

IRCClient *IRCClientsManager::FindOrCreateClient(IRCSocket *socket)
{
    IRCClient *client;
    std::unordered_map<IRCSocket*, IRCClient*>::iterator it = m_SocketClientsMap.find(socket);
    
    if (it != m_SocketClientsMap.end())
    {
        client = it->second;
    }
    else
    {
        client = New(IRCClient);
        m_SocketClientsMap[socket] = client;
        IRC_LOGD("%s", "Client created");
    }
    return client;
}

IRCClient *IRCClientsManager::FindClientByNickname(const std::string& nickname)
{
    for ( std::unordered_map<IRCSocket*, IRCClient*>::iterator it = m_SocketClientsMap.begin(); it != m_SocketClientsMap.end(); ++it)
    {
        if (it->second->GetNickname() == nickname)
        {
            return it->second;
        }
    }
    return NULL;
}

}
