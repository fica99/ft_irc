#include "main/precomp.h"

#include "ircmessages/tokens/irctoken.h"

namespace ircserv
{

IRCToken::IRCToken()
{
    Initialize();
}

void IRCToken::Initialize(void)
{
}


IRCToken::~IRCToken()
{
    Shutdown();
}

void IRCToken::Shutdown(void)
{
}

}
