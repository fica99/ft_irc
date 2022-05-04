#pragma once

#include "irccommands/irccommand.h"

namespace ircserv
{

class IRCModeCommand : public IRCCommand
{
public:
    IRCModeCommand();
    virtual ~IRCModeCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(/*serverclass */);

private:
    bool ValidateArgs(/*serverclass */);

};

}
