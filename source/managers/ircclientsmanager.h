#pragma once

#include <unordered_map>
#include <string>

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
    IRCClient *CreateClient(IRCSocket *socket);
    IRCClient *FindClient(IRCSocket *socket) const;
    IRCClient *FindOrCreateClient(IRCSocket *socket);
    IRCClient *FindClientByNickname(const std::string& nickname) const;
    IRCSocket *FindSocketByClient(IRCClient *client) const;
    void EraseClient(IRCSocket *socket);

public:
    inline const std::unordered_map<IRCSocket*, IRCClient*>& GetSocketsClientsMap(void) const { return m_SocketsClientsMap; }
    inline const std::unordered_map<std::string, std::string>& GetOpersMap(void) const { return m_OpersMap; }

private:
    std::unordered_map<IRCSocket*, IRCClient*> m_SocketsClientsMap;
    std::unordered_map<std::string, std::string> m_OpersMap;
};

#define GetIRCClientsManager() IRCClientsManager::GetInstance()

}
