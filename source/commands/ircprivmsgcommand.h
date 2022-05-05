#pragma once

#include "commands/irccommand.h"

namespace ircserv
{

class IRCPrivmsgCommand : public IRCCommand
{
public:
    IRCPrivmsgCommand();
    virtual ~IRCPrivmsgCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(/*serverclass */);

private:
    bool ValidateArgs(/*serverclass */);
};

}
