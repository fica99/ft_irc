#pragma once

#include <string>

#include "ircmessages/tokens/irctoken.h"

namespace ircserv
{

class IRCPrefixToken : public IRCToken
{
public:
    IRCPrefixToken(const std::string& rawStr, const std::string& prefix = ":");
    virtual ~IRCPrefixToken();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    inline const std::string& GetPrefix(void) const { return m_Prefix; }
    inline const std::string& GetProcessedStr(void) const { return m_ProcessedStr; }

private:
    std::string m_Prefix;
    std::string m_ProcessedStr;
};

}

