#pragma once

#include "irccommands/irccommand.h"

namespace ircserv
{

class IRCVersionCommand : public IRCCommand
{
public:
    IRCVersionCommand();
    virtual ~IRCVersionCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(/*serverclass */);

private:
    bool ValidateArgs(/*serverclass */);
};

}
