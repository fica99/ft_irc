#include "main/precomp.h"

#include "ircmessages/tokens/ircargtoken.h"

namespace ircserv
{

IRCArgToken::IRCArgToken()
{
    Initialize();
}

void IRCArgToken::Initialize(void)
{
}


IRCArgToken::~IRCArgToken()
{
    Shutdown();
}

void IRCArgToken::Shutdown(void)
{
}


}
