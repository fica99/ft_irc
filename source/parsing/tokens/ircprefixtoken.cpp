#include "main/precomp.h"

#include "parsing/tokens/ircprefixtoken.h"

namespace ircserv
{

IRCPrefixToken::IRCPrefixToken()
{
    Initialize();
}

void IRCPrefixToken::Initialize(void)
{
}


IRCPrefixToken::~IRCPrefixToken()
{
    Shutdown();
}

void IRCPrefixToken::Shutdown(void)
{
}


}
