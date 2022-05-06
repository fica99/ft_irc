#pragma once

#include <string>

#include "server/commands/parsing/tokens/irctoken.h"

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
    inline const std::string& GetNick(void) const { return m_Nick; }
    inline void SetUser(const std::string& user) { m_User = user; }
    inline const std::string& GetUser(void) const { return m_User; }
    inline void SetHost(const std::string& host) { m_Host = host; }
    inline const std::string& GetHost(void) const { return m_Host; }

private:
    std::string m_Nick;
    std::string m_User;
    std::string m_Host;
};

}

