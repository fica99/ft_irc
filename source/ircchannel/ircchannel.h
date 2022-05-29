#pragma once

#include <string>
#include <set>

#include "ircserver/ircsocket.h"

namespace ircserv
{

class IRCChannel
{
public:
    IRCChannel();
    virtual ~IRCChannel();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    inline void SetIsInviteOnly(bool isInviteOnly) { m_IsInviteOnly = isInviteOnly; }
    inline bool GetIsInviteOnly(void) const { return m_IsInviteOnly; }
    inline void SetName(const std::string& name) { m_Name = name; }
    inline const std::string& GetName(void) const { return m_Name; }
    inline void SetKey(const std::string& key) { m_Key = key; }
    inline const std::string& GetKey(void) const { return m_Key; }
    inline void SetTopic(const std::string& topic) { m_Topic = topic; }
    inline const std::string& GetTopic(void) const { return m_Topic; }
    inline void SetOperator(IRCSocket *oper) { m_Operator = oper; }
    inline IRCSocket* GetOperator(void) const { return m_Operator; }
    inline bool AddUser(IRCSocket* user) { return m_Users.insert(user).second; }
    inline const std::set<IRCSocket*>& GetUsers(void) const { return m_Users; }

private:
    bool m_IsInviteOnly;
    std::string m_Name;
    std::string m_Key;
    std::string m_Topic;
    IRCSocket* m_Operator;
    std::set<IRCSocket*> m_Users;
};


}
