#include "main/precomp.h"

#include "ircserver/ircserver.h"
#include "managers/irccommandsmanager.h"
#include "utils/memory.h"

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
    IRC_LOGD("Received signal! Signal number: %d", sigNum);
    GetIRCServer().Stop();
    exit(sigNum);
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
    for (size_t i = 0; i < m_AcceptedSockets.size(); ++i)
    {
        m_AcceptedSockets[i]->CloseSocket();
        Delete(m_AcceptedSockets[i]);
    }
    m_AcceptedSockets.clear();
    m_ListenSocket.CloseSocket();
}

void IRCServer::GetAllSockets(std::vector<IRCSocket*>& sockets)
{
    sockets.clear();
    sockets.push_back(&m_ListenSocket);
    sockets.insert(sockets.begin() + 1, m_AcceptedSockets.begin(), m_AcceptedSockets.end());
}

void IRCServer::CloseConnection(IRCSocket *socket)
{
    socket->CloseSocket();
    std::vector<IRCSocket*>::iterator it = std::find(m_AcceptedSockets.begin(), m_AcceptedSockets.end(), socket);
    if (it != m_AcceptedSockets.end())
    {
        Delete(*it);
        m_AcceptedSockets.erase(it);
    }
}

std::string IRCServer::ReceiveMsg(IRCSocket *socket)
{
    std::string msg;
    int nbytes;

    if (socket != NULL)
    {
        nbytes = socket->Recv(msg);
        if (nbytes == 0)
        {
            CloseConnection(socket);
        }
    }
    return msg;
}

void IRCServer::ProcessSelectedSockets(const std::vector<IRCSocket*>& sockets)
{
    IRCSocket *connection;
    std::string msg;

    for (size_t i = 0; i < sockets.size(); ++i)
    {
        if (sockets[i] == &m_ListenSocket)
        {
            connection = m_ListenSocket.Accept();
            if (connection != NULL)
            {
                m_AcceptedSockets.push_back(connection);
            }
        }
        else
        {
            msg = ReceiveMsg(sockets[i]);
            GetIRCCommandsManager().ProcessCommand(msg, sockets[i]);
        }
    }
}

void IRCServer::ServerLoop(void)
{
    std::vector<IRCSocket*> sockets;
    int socketsSelected;

    IRC_LOGI("%s", "The server is waiting for connections...");
    while (GetIsRunning())
    {
        GetAllSockets(sockets);
        socketsSelected = IRCSocket::Select(sockets, 1);
        if (socketsSelected > 0)
        {
            ProcessSelectedSockets(sockets);
        }
        IRC_LOGI("Total number of connections: %d", m_AcceptedSockets.size());
        sockets.clear();
    }
}

void IRCServer::SetIsRunning_Callback(bool isRunning)
{
    if (m_IsRunning == isRunning)
    {
        return;
    }

    m_IsRunning = isRunning;
    if (isRunning == true)
    {
        IRC_LOGI("%s", "Server is started");
    }
    else
    {
        IRC_LOGI("%s", "Server is stopped");
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
