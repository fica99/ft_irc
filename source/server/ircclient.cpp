#include "main/precomp.h"

#include "server/ircclient.h"

namespace ircserv
{

IRCClient::IRCClient() : errcode(0), registered(false) 
{
}

IRCClient::~IRCClient()
{
}

}
