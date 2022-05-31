#include "main/precomp.h"

#include "ircclient/ircclient.h"

#define MAX_NB_JOINED_CHANNELS 10
#define DEFAULT_HOST_NAME "127.0.0.1"

namespace ircserv
{

IRCClient::IRCClient()
{
    Initialize();
}

void IRCClient::Initialize(void)
{
    m_Modes = 0;
    m_Hostname = DEFAULT_HOST_NAME;
    m_MaxNbJoinedChannels = MAX_NB_JOINED_CHANNELS;
}

IRCClient::~IRCClient()
{
    Shutdown();
}

void IRCClient::Shutdown(void)
{
}

}
