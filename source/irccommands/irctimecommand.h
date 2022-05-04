#pragma once

#include "irccommands/irccommand.h"

namespace ircserv
{

class IRCTimeCommand : public IRCCommand
{
public:
    IRCTimeCommand();
    virtual ~IRCTimeCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(/*serverclass */);

private:
    bool ValidateArgs(/*serverclass */);
};

}
