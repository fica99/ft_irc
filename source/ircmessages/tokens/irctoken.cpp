#include "main/precomp.h"

#include "ircmessages/tokens/irctoken.h"

namespace ircserv
{

IRCToken::IRCToken(const std::string& rawStr) : m_RawStr(rawStr)
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
