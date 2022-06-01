#pragma once

#include <string>

#include "irccommands/irccommand.h"

namespace ircserv
{

class IRCInviteCommand : public IRCCommand
{
public:
    IRCInviteCommand();
    virtual ~IRCInviteCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(IRCSocket *socket);

private:
    bool ValidateArgs(IRCSocket *socket);

private:
    inline void SetNickname(const std::string& nickname) { m_Nickname = nickname; }
    inline const std::string& GetNickname(void) const { return m_Nickname; }
    inline void SetChannel(const std::string& channel) { m_Channel = channel; }
    inline const std::string& GetChannel(void) const { return m_Channel; }

private:
    std::string m_Nickname;
    std::string m_Channel;

};

}
