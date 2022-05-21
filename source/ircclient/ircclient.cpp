#include "main/precomp.h"

#include "ircclient/ircclient.h"

namespace ircserv
{

IRCClient::IRCClient() : m_Fd(0)
{
    Initialize();
}

void IRCClient::Initialize(void)
{
}

IRCClient::~IRCClient()
{
    Shutdown();
}

void IRCClient::Shutdown(void)
{
}

}
