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
    bool ProcessCommand(/*serverclass */);

private:
    bool ValidateArgs(/*serverclass */);

private:
    bool SetNickname(const std::string& arg);
private:
    std::string m_Nickname;

};

}
