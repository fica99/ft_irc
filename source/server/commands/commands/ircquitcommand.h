#pragma once

#include <string>

#include "server/commands/commands/irccommand.h"

namespace ircserv
{

class IRCQuitCommand : public IRCCommand
{
public:
    IRCQuitCommand();
    virtual ~IRCQuitCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(Server *serv);

private:
    bool ValidateArgs(/*serverclass */);

private:
    inline void SetQuitMessage(const std::string quitMessage) { m_QuitMessage = quitMessage; }

private:
    std::string m_QuitMessage;
};

}
