#include "main/precomp.h"

#include "managers/ircclientsmanager.h"
#include "utils/memory.h"

#include <fcntl.h>

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
    m_FdClientsMap.clear();
    for (std::list<IRCClient*>::iterator it = m_Clients.begin(); it != m_Clients.end(); ++it)
    {
        Delete(*it);
    }
    m_Clients.clear();
    m_PollFds.clear();
}

void IRCClientsManager::AddClient(int fd)
{
    std::unordered_map<int, std::list<IRCClient*>::iterator>::iterator it = m_FdClientsMap.find(fd);

    if (it != m_FdClientsMap.end())
    {
        return;
    }

    IRCClient *client = New(IRCClient);
    client->SetFd(fd);
    m_Clients.push_back(client);
    
    m_FdClientsMap[fd] = --m_Clients.end();

    struct pollfd pollFd;
    fcntl(fd, F_SETFL, O_NONBLOCK);
    pollFd.fd = fd;
    pollFd.events = POLLIN;
    m_PollFds.push_back(pollFd);
}

void IRCClientsManager::RemoveClient(int fd)
{
    std::unordered_map<int, std::list<IRCClient*>::iterator>::iterator it = m_FdClientsMap.find(fd);

    if (it == m_FdClientsMap.end())
    {
        return;
    }

    Delete(*(it->second));
    m_PollFds.erase(m_PollFds.begin() + std::distance(m_Clients.begin(), it->second));
    m_Clients.erase(it->second);
    m_FdClientsMap.erase(it);
}

}
