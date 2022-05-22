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
    int fd;
    struct sockaddr_storage theirAddr;
    socklen_t sinSize = sizeof(theirAddr);

    if (GetIsRunning() == false)
    {
        return;
    }

    fd = accept(m_ListenSockFd, (struct sockaddr *)&theirAddr, &sinSize);
    if (fd == -1)
    {
        IRC_LOGD("accept error: %s", strerror(errno));
        return;
    }

    GetIRCClientsManager().AddClient(fd);
    IRC_LOGI("%s", "New connection accepted");
}

bool IRCServer::StartServer(void)
{
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int yes = 1;
    int sockfd;
    std::string port;
    std::stringstream out;

    out << m_Port;
    port = out.str();

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if ((rv = getaddrinfo(NULL, port.c_str(), &hints, &servinfo)) != 0)
    {
        IRC_LOGE("getaddrinfo error: %s", gai_strerror(rv));
        return false;
    }

    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            IRC_LOGE("socket error: %s", strerror(errno));
            continue;
        }
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        {
            IRC_LOGE("setsockopt error: %s", strerror(errno));
            return false;
        }
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            IRC_LOGE("bind error: %s", strerror(errno));
            continue;
        }
        break;
    }
    if (p == NULL)
    {
        IRC_LOGE("server: %s", "failed to bind");
        return false;
    }

    m_ListenSockFd = sockfd;

    freeaddrinfo(servinfo);

    if (listen(m_ListenSockFd, LISTEN_QUEUE) != 0)
    {
        IRC_LOGE("listen error: %s", strerror(errno));
        return false;
    }

    IRC_LOGD("Server socket created, binded and listens! FD: %d", m_ListenSockFd);
    return true;
}

bool IRCServer::StopServer(void)
{
    if (close(m_ListenSockFd) == 0)
    {
        IRC_LOGD("Listen FD is closed! FD: %d", m_ListenSockFd);
    }
    else
    {
        IRC_LOGE("close listen FD error: %s! FD: %d", strerror(errno), m_ListenSockFd);
        return false;
    }
    return true;
}

}
