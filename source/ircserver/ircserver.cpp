#include "main/precomp.h"

#include "ircserver/ircserver.h"
#include "managers/ircclientsmanager.h"
#include "managers/irccommandsmanager.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>

#define LISTEN_QUEUE 128

namespace ircserv
{

IMPLEMENT_SIMPLE_SINGLETON(IRCServer);

IRCServer::IRCServer()
{
    IMPLEMENT_SIMPLE_SINGLETON_CONSTRUCTOR();

    Initialize();
}

static void SigHandler(int sigNum)
{
    IRC_LOGD("Received SIGINT(sigNum: %d), server is stopped", sigNum);
    GetIRCServer().SetIsRunning(false);
}

void IRCServer::Initialize(void)
{
    m_IsRunning = false;
    m_Port = 0;
    IRCClientsManager::CreateSingleton();
    IRCCommandsManager::CreateSingleton();
    signal(SIGINT, &SigHandler);
}

IRCServer::~IRCServer()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void IRCServer::Shutdown(void)
{
    SetIsRunning(false);
    IRCCommandsManager::DestroySingleton();
    IRCClientsManager::DestroySingleton();
    m_IsRunning = false;
    m_Port = 0;
    m_Password.clear();
}

void IRCServer::SetIsRunning_Callback(bool isRunning)
{
    if (isRunning == m_IsRunning)
    {
        return;
    }

    if (isRunning == true)
    {
        if (StartServer() == true)
        {
            m_IsRunning = true;
        }
    }
    else
    {
        m_IsRunning = false;
        StopServer();
    }
}

void IRCServer::SetPort_Callback(unsigned short int port)
{
    if (!GetIsRunning())
    {
        m_Port = port;
    }
    else
    {
        IRC_LOGD("%s", "Cannot change port while server running. Please, stop server");
    }
}

void IRCServer::SetPassword_Callback(const std::string& password)
{
    if (!GetIsRunning())
    {
        m_Password = password;
    }
    else
    {
        IRC_LOGD("%s", "Cannot change password while server running. Please, stop server");
    }
}

void IRCServer::AcceptNewConnection(void) const
{
    // int fd;
    // struct sockaddr_storage theirAddr;
    // socklen_t sinSize = sizeof(theirAddr);

    // if (GetIsRunning() == false)
    // {
    //     return;
    // }

    // fd = accept(m_ListenSockFd, (struct sockaddr *)&theirAddr, &sinSize);
    // if (fd == -1)
    // {
    //     IRC_LOGD("accept error: %s", strerror(errno));
    //     return;
    // }

    // GetIRCClientsManager().AddClient(fd);
    // IRC_LOGI("%s", "New connection accepted");
}

bool IRCServer::StartServer(void)
{
    return m_ListenSocket.CreateListenSocket(m_Port);
}

void IRCServer::StopServer(void)
{
    m_ListenSocket.CloseSocket();
}

}
