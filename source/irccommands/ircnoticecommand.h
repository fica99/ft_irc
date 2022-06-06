#pragma once

#include <string>

#include "irccommands/irccommand.h"

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
    bool ProcessCommand(IRCSocket *socket);

private:
    bool ValidateArgs(IRCSocket *socket);

private:
    inline void SetNickname(const std::string& nickname) { m_Nickname = nickname; }
    inline const std::string& GetNickname(void) const { return m_Nickname; }
    inline void SetText(const std::string& text) { m_Text = text; }
    inline const std::string& GetText(void) const { return m_Text; }
private:
    std::string m_Nickname;
    std::string m_Text;

};

}
