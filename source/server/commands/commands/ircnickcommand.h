#pragma once

#include <string>

#include "server/commands/commands/irccommand.h"

namespace ircserv
{

class IRCNickCommand : public IRCCommand
{
public:
    IRCNickCommand();
    virtual ~IRCNickCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(IRCServer *serv);

private:
    bool ValidateArgs(/*serverclass */);

private:
    inline void SetNickname(const std::string& nickname) { m_Nickname = nickname; }
private:
    std::string m_Nickname;

};

}
