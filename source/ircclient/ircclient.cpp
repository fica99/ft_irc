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
    m_IsOper = false;
    m_NumberJoinedChannels = 0;
}

IRCClient::~IRCClient()
{
    Shutdown();
}

void IRCClient::Shutdown(void)
{
}

}
