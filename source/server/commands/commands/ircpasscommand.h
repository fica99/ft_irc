#pragma once

#include <string>

#include "server/commands/commands/irccommand.h"

namespace ircserv
{

class IRCPassCommand : public IRCCommand
{
public:
    IRCPassCommand();
    virtual ~IRCPassCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(IRCServer *serv);

private:
    bool ValidateArgs(/*serverclass */);

private:
    inline void SetPassword(const std::string& password) { m_Password = password; }

private:
    std::string m_Password;
};

}
