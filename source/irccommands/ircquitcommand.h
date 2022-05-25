#pragma once

#include <string>

#include "irccommands/irccommand.h"

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
    bool ProcessCommand(IRCSocket *socket);

private:
    bool ValidateArgs(IRCSocket *socket);

private:
    inline void SetQuitMessage(const std::string quitMessage) { m_QuitMessage = quitMessage; }
    inline const std::string& GetQuitMessage(void) const { return m_QuitMessage; }


private:
    std::string m_QuitMessage;
};

}
