#pragma once

#include <unordered_map>
#include <list>
#include <vector>
#include <poll.h>

#include "ircclient/ircclient.h"
#include "utils/singleton.h"

namespace ircserv
{

class IRCClientsManager
{
public:
    IRCClientsManager();
    virtual ~IRCClientsManager();
    DECLARE_SIMPLE_SINGLETON(IRCClientsManager);
private:
    void Initialize(void);
    void Shutdown(void);

public:
    void AddClient(int fd);
    void RemoveClient(int fd);
    inline IRCClient* GetClient(int fd) const { return *(m_FdClientsMap.at(fd)); }
    inline pollfd* GetPollFdsData(void) { return m_PollFds.data(); }

private:
    std::unordered_map<int, std::list<IRCClient*>::iterator> m_FdClientsMap;
    std::list<IRCClient*> m_Clients;
    std::vector<struct pollfd> m_PollFds;
};

#define GetIRCClientsManager() IRCClientsManager::GetInstance()

}
