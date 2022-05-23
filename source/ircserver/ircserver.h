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

private:
    void ServerLoop(void);

private:
    void SetPort_Callback(uint16_t port);
    void SetPassword_Callback(const std::string& password);

public:
    inline void SetPort(uint16_t port) { SetPort_Callback(port); }
    inline uint16_t GetPort(void) const { return m_Port; }
    inline void SetPassword(const std::string& password) { SetPassword_Callback(password); }
    inline const std::string& GetPassword(void) const { return m_Password; }

private:
    inline void SetIsRunning(bool isRunning) { m_IsRunning = isRunning; }
    inline bool GetIsRunning(void) const { return m_IsRunning; }


private:
    bool m_IsRunning;
    uint16_t m_Port;
    std::string m_Password;
    IRCSocket m_ListenSocket;
    std::vector<IRCSocket*> m_ConnectionSockets;
};

#define GetIRCServer() IRCServer::GetInstance()


}
