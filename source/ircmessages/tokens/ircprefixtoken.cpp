#include "main/precomp.h"

#include "ircmessages/tokens/ircprefixtoken.h"

namespace ircserv
{

IRCPrefixToken::IRCPrefixToken(const std::string& rawStr, const std::string& prefix)
    : IRCToken(rawStr)
    , m_Prefix(prefix)
{
    Initialize();

    if (!rawStr.compare(0, prefix.size(), prefix))
    {
        m_ProcessedStr = rawStr.substr(prefix.size());
    }
    else
    {
        throw std::invalid_argument("Invalid prefix token: " + rawStr);
    }
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
