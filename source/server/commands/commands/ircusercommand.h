#pragma once

#include <string>

#include "server/commands/commands/irccommand.h"

namespace ircserv
{

class IRCUserCommand : public IRCCommand
{
public:
    IRCUserCommand();
    virtual ~IRCUserCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(/*serverclass */);

private:
    bool ValidateArgs(/*serverclass */);

private:
    bool SetUsername(const std::string& arg);
    bool SetRealname(const std::string& arg);

private:
    std::string m_Username;
    std::string m_Realname;
};

}
