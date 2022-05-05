#include "main/precomp.h"

#include "commandsprocessing/tokens/irctoken.h"

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
