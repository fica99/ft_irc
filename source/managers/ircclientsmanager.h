#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "ircclient/ircclient.h"
#include "ircserver/ircsocket.h"
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
    IRCClient *FindOrCreateClient(IRCSocket *socket);
    IRCClient *FindClient(IRCSocket *socket);
    IRCClient *FindClientByNickname(const std::string& nickname) const;
 
    void EraseClient(IRCSocket *socket);
    void AddOper(const std::string& user, const std::string& password);
    bool IsRegistered(IRCSocket *socket);
    bool IsOper(const std::string& user, const std::string& password);
    inline bool IsOperMapEmpty(void) const { return m_OpersMap.empty(); }
    std::vector<IRCClient*> GetAllClients(void) const;

private:
    std::unordered_map<IRCSocket*, IRCClient*> m_SocketClientsMap;
    std::unordered_map<std::string, std::string> m_OpersMap;
};

#define GetIRCClientsManager() IRCClientsManager::GetInstance()

}
