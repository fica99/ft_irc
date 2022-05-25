#pragma once

#include <unordered_map>
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

private:
    std::unordered_map<IRCSocket*, IRCClient*> m_SocketClientsMap;
};

#define GetIRCClientsManager() IRCClientsManager::GetInstance()

}
