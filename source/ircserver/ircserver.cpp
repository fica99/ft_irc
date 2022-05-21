#include "main/precomp.h"

#include "ircserver/ircserver.h"
#include "managers/ircclientsmanager.h"
#include "managers/irccommandsmanager.h"

#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>

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
    signal(SIGINT, &SigHandler);
    IRCClientsManager::CreateSingleton();
    IRCCommandsManager::CreateSingleton();
}

IRCServer::~IRCServer()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void IRCServer::Shutdown(void)
{
    IRCCommandsManager::DestroySingleton();
    IRCClientsManager::DestroySingleton();
    m_IsRunning = false;
    m_Port = 0;
}

void IRCServer::SetIsRunning_Callback(bool isRunning)
{
    if (isRunning == true)
    {
        if (m_Port != 0)
        {
            if (BindServerFd() == true)
            {
                m_IsRunning = true;
            }
        }
    }
    else
    {
        m_IsRunning = false;
        CloseServerFd();
    }
}

void IRCServer::SetPort_Callback(unsigned short int port)
{
    if (!GetIsRunning())
    {
        m_Port = port;
    }
}

void IRCServer::SetPassword_Callback(const std::string& password)
{
    if (!GetIsRunning())
    {
        m_Password = password;
    }
}

void IRCServer::AcceptNewConnection(void) const
{
    int fd;
    static size_t addrlen = sizeof(struct sockaddr_in);

    if (GetIsRunning() == false)
    {
        return;
    }

    fd = accept(m_ServerFd, (sockaddr *)&m_Servaddr, (socklen_t *)(&addrlen));
    if (fd >= 0)
    {
        // struct pollfd pfd;

        // fcntl(userFd, F_SETFL, O_NONBLOCK);
        // pfd.fd = userFd;
        // pfd.events = POLLIN;;
        GetIRCClientsManager().AddClient(fd);
        IRC_LOGI("%s", "New connection accepted");
    }
}


bool IRCServer::BindServerFd(void)
{
    static const int on = 1;

    memset(&m_Servaddr, 0, sizeof(m_Servaddr));
    m_ServerFd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_ServerFd == -1)
    {
        IRC_LOGE("socket error: %s", strerror(errno));
        return false;
    }

    m_Servaddr.sin_family = AF_INET;
    m_Servaddr.sin_addr.s_addr = INADDR_ANY;
    m_Servaddr.sin_port = htons(m_Port);

    if (fcntl(m_ServerFd, F_SETFL, O_NONBLOCK) == -1)
    {
        IRC_LOGE("fcntl error: %s", strerror(errno));
        return false;
    }
    if (setsockopt(m_ServerFd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int)) == -1)
    {
        IRC_LOGE("setsockopt error: %s", strerror(errno));
        return false;
    }
    if (bind(m_ServerFd, (struct sockaddr *)&m_Servaddr, sizeof(m_Servaddr)) == -1)
    {
        IRC_LOGE("bind error: %s", strerror(errno));
        return false;
    }
    if (listen(m_ServerFd, LISTEN_QUEUE) != 0)
    {
        IRC_LOGE("listen error: %s", strerror(errno));
        return false;
    }

    IRC_LOGD("Server socket created, binded and listens! FD: %d", m_ServerFd);
    return true;
}

bool IRCServer::CloseServerFd(void)
{
    if (close(m_ServerFd) == 0)
    {
        IRC_LOGD("Server is closed! FD: %d", m_ServerFd);
    }
    else
    {
        IRC_LOGE("close error: %s", m_ServerFd, strerror(errno));
        return false;
    }
    return true;
}

}
