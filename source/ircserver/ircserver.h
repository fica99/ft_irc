#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "ircserver/ircsocket.h"
#include "utils/singleton.h"

namespace ircserv
{

class IRCServer
{
public:
    IRCServer();
    virtual ~IRCServer();
private:
    void Initialize(void);
    void Shutdown(void);
    DECLARE_SIMPLE_SINGLETON(IRCServer);

public:
    void Start(void);
    void Stop(void);
    void CloseConnection(IRCSocket *socket);

private:
    void GetAllSockets(std::vector<IRCSocket*>& sockets);
    std::string ReceiveMsg(IRCSocket *socket);
    void ProcessSelectedSockets(const std::vector<IRCSocket*>& sockets);
    void ServerLoop(void);

private:
    void SetIsRunning_Callback(bool isRunning);
    void SetPort_Callback(uint16_t port);
    void SetPassword_Callback(const std::string& password);

public:
    inline void SetPort(uint16_t port) { SetPort_Callback(port); }
    inline uint16_t GetPort(void) const { return m_Port; }
    inline void SetPassword(const std::string& password) { SetPassword_Callback(password); }
    inline const std::string& GetPassword(void) const { return m_Password; }
    inline void SetIsRunning(bool isRunning) { SetIsRunning_Callback(isRunning); }
    inline bool GetIsRunning(void) const { return m_IsRunning; }
    inline void SetServerName(const std::string& serverName) { m_ServerName = serverName; }
    inline const std::string GetServerName(void) const { return m_ServerName; }

private:
    bool m_IsRunning;
    uint16_t m_Port;
    std::string m_Password;
    std::string m_ServerName;
    IRCSocket m_ListenSocket;
    std::vector<IRCSocket*> m_AcceptedSockets;
};

#define GetIRCServer() IRCServer::GetInstance()


}
