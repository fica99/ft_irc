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
        IRC_LOGD("%s", "Client disconnected");
    }
    GetIRCServer().CloseConnection(socket);
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
    bool wasRegistered = client->GetIsRegistered();
    client->SetNickname(nickname);
    if (client->GetIsRegistered() == true)
    {
        if (client->GetPassword() != GetIRCServer().GetPassword())
        {
            Quit(socket, "");
        }
        else if (wasRegistered == false)
        {
            return Enum_IRCResponses_RPL_MOTD;
        }
    }
    return Enum_IRCResponses_Unknown;
}

Enum_IRCResponses IRCClientsManager::User(IRCSocket *socket, const std::string& username, const std::string& realname)
{
    IRCClient *client = FindOrCreateClient(socket);
    if (client->GetIsRegistered())
    {
        return Enum_IRCResponses_ERR_ALREADYREGISTRED;
    }
    client->SetUsername(username);
    client->SetRealname(realname);
    if (client->GetIsRegistered() == true)
    {
        if (client->GetPassword() != GetIRCServer().GetPassword())
        {
            Quit(socket, "");
        }
        else
        {
            return Enum_IRCResponses_RPL_MOTD;
        }
    }
    return Enum_IRCResponses_Unknown;
}

Enum_IRCResponses IRCClientsManager::Oper(IRCSocket *socket, const std::string& user, const std::string& password)
{
    IRCClient *client = FindClient(socket);

    if (!m_OpersMap.empty())
    {
        std::unordered_map<std::string, std::string>::iterator it = m_OpersMap.find(user);
        if (it != m_OpersMap.end())
        {
            if (password == it->second)
            {
                if (client)
                {
                    client->SetIsOper(true);
                }
                return Enum_IRCResponses_RPL_YOUREOPER;
            }
        }
        return Enum_IRCResponses_ERR_PASSWDMISMATCH;
    }
    return Enum_IRCResponses_ERR_NOOPERHOST;
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

void IRCClientsManager::AddOper(const std::string& user, const std::string& password)
{
    m_OpersMap[user] = password;
}


}
