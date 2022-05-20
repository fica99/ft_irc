#include "main/precomp.h"

#include "ircserver/ircserver.h"

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
    (void)sigNum;
    GetIRCServer().SetIsRunning(false);
}

void IRCServer::Initialize(void)
{
    m_IsRunning = false;
    m_Port = 0;
    signal(SIGINT, &SigHandler);
}

IRCServer::~IRCServer()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void IRCServer::Shutdown(void)
{
    m_IsRunning = false;
    m_Port = 0;
}

void IRCServer::SetIsRunning_Callback(bool isRunning)
{
    if (isRunning == true)
    {
        if (m_Port != 0)
        {
            BindServerFd();
            m_IsRunning = true;
        }
    }
    else
    {
        m_IsRunning = false;
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

void IRCServer::BindServerFd(void)
{
    static const int on = 1;

    memset(&m_Servaddr, 0, sizeof(m_Servaddr));
    m_ServerFd = socket(AF_INET, SOCK_STREAM, 0);
    m_Servaddr.sin_family = AF_INET;
    m_Servaddr.sin_addr.s_addr = INADDR_ANY;
    m_Servaddr.sin_port = htons(m_Port);

    fcntl(m_ServerFd, F_SETFL, O_NONBLOCK);
    setsockopt(m_ServerFd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));
    if (bind(m_ServerFd, (struct sockaddr *)&m_Servaddr, sizeof(m_Servaddr)) < 0)
    {
        IRC_LOGE("Bind error: %s", strerror(errno));
    }
    listen(m_ServerFd, LISTEN_QUEUE);
}

void IRCServer::CloseServerFd(void)
{
    close(m_ServerFd);
}

}
