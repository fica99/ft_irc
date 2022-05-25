#pragma once

#include <string>

namespace ircserv
{

class IRCClient
{
public:
    IRCClient();
    virtual ~IRCClient();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    inline void SetIsRegistered(bool isRegistered) { m_IsRegistered = isRegistered; };
    inline bool GetIsRegistered(void) const { return m_IsRegistered; }
    inline void SetPassword(const std::string& password) { m_Password = password; }
    inline const std::string& GetPassword(void) { return m_Password; }

private:
    bool m_IsRegistered;
    std::string m_Password;
};


}
