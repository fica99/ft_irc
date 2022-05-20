#pragma once

#include <string>

#include "irccommands/irccommand.h"

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
    bool ProcessCommand(void);

private:
    bool ValidateArgs(void);

private:
    inline void SetPassword(const std::string& password) { m_Password = password; }

private:
    std::string m_Password;
};

}
