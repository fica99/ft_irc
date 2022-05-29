#pragma once

#include <unordered_map>
#include "ircresponses/ircresponses.h"
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
    void Quit(IRCSocket *socket, const std::string& quitMessage);
    bool Pass(IRCSocket *socket, const std::string& password);
    Enum_IRCResponses Nick(IRCSocket *socket, const std::string& nickname);
    Enum_IRCResponses User(IRCSocket *socket, const std::string& username, const std::string& realname);
    Enum_IRCResponses Oper(IRCSocket *socket, const std::string& user, const std::string& password);

public:
    IRCClient *FindOrCreateClient(IRCSocket *socket);
    IRCClient *FindClient(IRCSocket *socket);
    IRCClient *FindClientByNickname(const std::string& nickname) const;
    void AddOper(const std::string& user, const std::string& password);
    bool IsRegistered(IRCSocket *socket);

private:
    std::unordered_map<IRCSocket*, IRCClient*> m_SocketClientsMap;
    std::unordered_map<std::string, std::string> m_OpersMap;
};

#define GetIRCClientsManager() IRCClientsManager::GetInstance()

}
