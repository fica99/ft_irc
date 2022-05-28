#include "main/precomp.h"

#include "ircchannel/ircchannel.h"

namespace ircserv
{

IRCChannel::IRCChannel()
{
    Initialize();
}

void IRCChannel::Initialize(void)
{
    m_IsInviteOnly = false;
}

IRCChannel::~IRCChannel()
{
    Shutdown();
}

void IRCChannel::Shutdown(void)
{
}

}
