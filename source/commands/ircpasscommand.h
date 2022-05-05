#pragma once

#include "commands/irccommand.h"

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
    bool ProcessCommand(/*serverclass */);

private:
    bool ValidateArgs(/*serverclass */);
};

}
