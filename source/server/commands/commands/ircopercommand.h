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
    bool ProcessCommand(/*serverclass */);

private:
    bool ValidateArgs(/*serverclass */);

private:
    bool SetUser(const std::string& arg);
    bool SetPassword(const std::string& arg);

private:
    std::string m_User;
    std::string m_Password;
};

}
