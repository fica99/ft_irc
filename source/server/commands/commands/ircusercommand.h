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
    inline void SetUsername(const std::string& username) { m_Username = username; }
    inline void SetRealname(const std::string& realname) { m_Realname = realname; }

private:
    std::string m_Username;
    std::string m_Realname;
};

}
