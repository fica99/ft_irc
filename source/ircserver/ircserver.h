#pragma once

#include <cstdint>
#include <string>

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

private:
    void SetIsRunning_Callback(bool isRunning);
    void SetPort_Callback(uint16_t port);
    void SetPassword_Callback(const std::string& password);

public:
    void SetIsRunning(bool isRunning) { SetIsRunning_Callback(isRunning); }
    bool GetIsRunning(void) const { return m_IsRunning; }
    void SetPort(uint16_t port) { SetPort_Callback(port); }
    uint16_t GetPort(void) const { return m_Port; }
    void SetPassword(const std::string& password) { SetPassword_Callback(password); }
    const std::string& GetPassword(void) const { return m_Password; }

public:
    void AcceptNewConnection(void) const;

private:
    bool StartServer(void);
    bool StopServer(void);

private:
    bool m_IsRunning;
    uint16_t m_Port;
    std::string m_Password;

private:
    int m_ListenSockFd;
};

#define GetIRCServer() IRCServer::GetInstance()


}
