#pragma once

#include "irccommands/irccommand.h"

namespace ircserv
{

class IRCPartCommand : public IRCCommand
{
public:
    IRCPartCommand();
    virtual ~IRCPartCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(/*serverclass */);

private:
    bool ValidateArgs(/*serverclass */);
};

}
