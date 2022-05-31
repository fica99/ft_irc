#pragma once

#include <string>
#include <unordered_set>

#define INVISIBLE       0b00000001
#define RECEIVENOTICE   0b00000010
#define RECEIVEWALLOPS  0b00000100
#define IRCOPERATOR     0b00001000

namespace ircserv
{

class IRCChannel;

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
    inline void SetHostname(const std::string& hostname) { m_Hostname = hostname; }
    inline const std::string& GetHostname(void) const { return m_Hostname; }
    inline void SetMaxNbJoinedChannels(size_t maxNbJoinedChannels) { m_MaxNbJoinedChannels = maxNbJoinedChannels; }
    inline size_t GetMaxNbJoinedChannels(void) const { return m_MaxNbJoinedChannels; }
    inline void SetModes(uint8_t modes) { m_Modes |= modes; }
    inline void UnsetModes(uint8_t modes) { m_Modes &= ~modes; }
    inline uint8_t GetModes(void) const { return m_Modes; }
    inline const std::unordered_set<IRCChannel*>& GetJoinedChannels(void) const { return m_JoinedChannels; }

public:
    inline bool JoinChannel(IRCChannel *channel) { return m_JoinedChannels.insert(channel).second; }
    inline void LeaveChannel(IRCChannel *channel) { m_JoinedChannels.erase(m_JoinedChannels.find(channel)); } 

private:
    std::string m_Password;
    std::string m_Nickname;
    std::string m_Username;
    std::string m_Realname;
    std::string m_Hostname;
    size_t m_MaxNbJoinedChannels;
    uint8_t m_Modes;
    std::unordered_set<IRCChannel*> m_JoinedChannels;

};


}
