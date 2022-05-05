#pragma once

#include "commands/irccommand.h"

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
};

}
