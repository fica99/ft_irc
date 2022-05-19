#pragma once

#include <string>

#include "server/commands/commands/irccommand.h"

namespace ircserv
{

class IRCOperCommand : public IRCCommand
{
public:
    IRCOperCommand();
    virtual ~IRCOperCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(IRCServer *serv);

private:
    bool ValidateArgs(IRCServer *serv);

private:
    inline void SetUser(const std::string& user) { m_User = user; }
    inline void SetPassword(const std::string& password) { m_Password = password; }

private:
    std::string m_User;
    std::string m_Password;
};

}
