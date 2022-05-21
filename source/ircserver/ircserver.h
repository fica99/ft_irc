#pragma once

#include <netinet/in.h>
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
    void SetPort_Callback(unsigned short int port);
    void SetPassword_Callback(const std::string& password);

public:
    void SetIsRunning(bool isRunning) { SetIsRunning_Callback(isRunning); }
    bool GetIsRunning(void) const { return m_IsRunning; }
    void SetPort(unsigned short int port) { SetPort_Callback(port); }
    unsigned short int GetPort(void) const { return m_Port; }
    void SetPassword(const std::string& password) { SetPassword_Callback(password); }
    const std::string& GetPassword(void) const { return m_Password; }

private:
    bool BindServerFd(void);
    bool CloseServerFd(void);

private:
    bool m_IsRunning;
    unsigned short int m_Port;
    std::string m_Password;

private:
    struct sockaddr_in m_Servaddr;
    int m_ServerFd;
};

#define GetIRCServer() IRCServer::GetInstance()


}
