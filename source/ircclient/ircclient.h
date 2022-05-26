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
    inline bool GetIsRegistered(void) const { return !GetNickname().empty() && !GetUsername().empty() && !GetRealname().empty(); }
    inline void SetPassword(const std::string& password) { m_Password = password; }
    inline const std::string& GetPassword(void) const { return m_Password; }
    inline void SetNickname(const std::string& nickname) { m_Nickname = nickname; }
    inline const std::string& GetNickname(void) const { return m_Nickname; }
    inline void SetUsername(const std::string& username) { m_Username = username; }
    inline const std::string& GetUsername(void) const { return m_Username; }
    inline void SetRealname(const std::string& realname) { m_Realname = realname; }
    inline const std::string& GetRealname(void) const { return m_Realname; }

private:
    std::string m_Password;
    std::string m_Nickname;
    std::string m_Username;
    std::string m_Realname;
};


}