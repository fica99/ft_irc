#include "main/precomp.h"

#include "ircclient/ircclient.h"

namespace ircserv
{

IRCClient::IRCClient()
{
    Initialize();
}

void IRCClient::Initialize(void)
{
    m_IsRegistered = false;
}

IRCClient::~IRCClient()
{
    Shutdown();
}

void IRCClient::Shutdown(void)
{
}

}
