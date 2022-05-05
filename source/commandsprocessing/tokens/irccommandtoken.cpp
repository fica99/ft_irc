#include "main/precomp.h"

#include "commandsprocessing/tokens/irccommandtoken.h"

namespace ircserv
{

IRCCommandToken::IRCCommandToken() : m_CommandNumber(0)
{
    Initialize();
}

void IRCCommandToken::Initialize(void)
{
}


IRCCommandToken::~IRCCommandToken()
{
    Shutdown();
}

void IRCCommandToken::Shutdown(void)
{
}

}
