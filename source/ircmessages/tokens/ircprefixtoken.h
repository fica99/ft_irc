#pragma once

#include <string>

#include "ircmessages/tokens/irctoken.h"

namespace ircserv
{

class IRCPrefixToken : public IRCToken
{
public:
    IRCPrefixToken();
    virtual ~IRCPrefixToken();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    inline void SetNick(const std::string& nick) { m_Nick = nick; }
    inline void SetUser(const std::string& user) { m_User = user; }
    inline void SetHost(const std::string& host) { m_Host = host; }

public:
    const std::string& GetPrefix(void) const;
private:
    std::string m_Nick;
    std::string m_User;
    std::string m_Host;
};

}

