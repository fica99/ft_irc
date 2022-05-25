#pragma once

#include <string>

#include "irccommands/irccommand.h"

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
    bool ProcessCommand(IRCSocket *socket);

private:
    bool ValidateArgs(IRCSocket *socket);

private:
    inline void SetUser(const std::string& user) { m_User = user; }
    inline void SetPassword(const std::string& password) { m_Password = password; }

private:
    std::string m_User;
    std::string m_Password;
};

}
