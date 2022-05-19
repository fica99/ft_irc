#pragma once

#include <string>

#include "server/commands/commands/irccommand.h"

namespace ircserv
{

class IRCNoticeCommand : public IRCCommand
{
public:
    IRCNoticeCommand();
    virtual ~IRCNoticeCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(IRCServer *serv);

private:
    bool ValidateArgs(IRCServer *serv);

private:
    inline void SetNickname(const std::string& nickname) { m_Nickname = nickname; }
    inline void SetText(const std::string& text) { m_Text = text; }
private:
    std::string m_Nickname;
    std::string m_Text;

};

}
