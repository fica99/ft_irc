#pragma once

#include <string>
#include <unordered_set>

#include "ircclient/ircclient.h"

#define PRIVATE     0b000001
#define SECRET      0b000010
#define MODERATED   0b000100
#define INVITEONLY  0b001000
#define TOPICSET    0b010000
#define NOMSGOUT    0b100000

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
    inline void SetName(const std::string& name) { m_Name = name; }
    inline const std::string& GetName(void) const { return m_Name; }
    inline void SetKey(const std::string& key) { m_Key = key; }
    inline const std::string& GetKey(void) const { return m_Key; }
    inline void SetTopic(const std::string& topic) { m_Topic = topic; }
    inline const std::string& GetTopic(void) const { return m_Topic; }
    inline void SetMaxUsersInChannel(size_t maxUsersInChannel) { m_MaxUsersInChannel = maxUsersInChannel; }
    inline size_t GetMaxUsersInChannel(void) const { return m_MaxUsersInChannel; }
    inline const std::unordered_set<IRCClient*>& GetClients(void) const { return m_Clients; }
    inline const std::unordered_set<IRCClient*>& GetOpers(void) const { return m_Opers; }
    inline const std::unordered_set<std::string>& GetBannedNicks(void) const { return m_BannedNicks; }
    inline void SetModes(uint8_t modes) { m_Modes |= modes; }
    inline void UnsetModes(uint8_t modes) { m_Modes &= ~modes; }
    inline uint8_t GetModes(void) const { return m_Modes; }

public:
    bool AddClient(IRCClient* client);
    void RemoveClient(IRCClient* client);
    inline void AddOper(IRCClient* oper) { m_Opers.insert(oper); }
    void RemoveOper(IRCClient* oper);
    inline void BanNick(const std::string& nick) { m_BannedNicks.insert(nick); }
    inline void UnbanNick(const std::string& nick);

private:
    std::string m_Name;
    std::string m_Key;
    std::string m_Topic;
    size_t m_MaxUsersInChannel;
    std::unordered_set<IRCClient*> m_Clients;
    std::unordered_set<IRCClient*> m_Opers;
    std::unordered_set<std::string> m_BannedNicks;
    uint8_t m_Modes;
};


}
