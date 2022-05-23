#include "main/precomp.h"

#include "ircserver/ircserver.h"

#include <signal.h>

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
    GetIRCServer().Stop();
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
    if (GetIsRunning())
    {
        Stop();
    }
}

void IRCServer::Start(void)
{
    if (GetIsRunning() == true)
    {
        return;
    }
    if (m_ListenSocket.CreateListenSocket(GetPort()) == true)
    {
        SetIsRunning(true);
        ServerLoop();
    }

}

void IRCServer::Stop(void)
{
    if (GetIsRunning() == false)
    {
        return;
    }
    SetIsRunning(false);
    m_ListenSocket.CloseSocket();
    for (size_t i = 0; i < m_ConnectionSockets.size(); ++i)
    {
        m_ConnectionSockets[i]->CloseSocket();
        delete m_ConnectionSockets[i];
    }
    m_ConnectionSockets.clear();
}

void IRCServer::ServerLoop(void)
{
    IRCSocket *connection;

    IRC_LOGI("%s", "The server is ready and waiting for connections...");
    while (GetIsRunning())
    {
        std::vector<IRCSocket*> reads;

        reads.push_back(&m_ListenSocket);
        reads.insert(reads.begin() + 1, m_ConnectionSockets.begin(), m_ConnectionSockets.end());

        if (IRCSocket::Select(reads, 0) < 1)
        {
            continue;
        }

        IRC_LOGD("%d socket descriptors changed", reads.size());

        for (size_t i = 0; i < reads.size(); ++i)
        {
            if (reads[i] == &m_ListenSocket)
            {
                connection = m_ListenSocket.Accept();
                if (connection != NULL)
                {
                    IRC_LOGI("New connection. Address: %s", connection->GetAddress().c_str());
                    m_ConnectionSockets.push_back(connection);
                }
            }
            else
            {
                IRC_LOGI("%s", "test");
            }
        }
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
        IRC_LOGD("%s", "Cannot change port while server is running. Please, stop server");
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

}
