#pragma once

#include "commands/irccommand.h"

namespace ircserv
{

class IRCKickCommand : public IRCCommand
{
public:
    IRCKickCommand();
    virtual ~IRCKickCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(/*serverclass */);

private:
    bool ValidateArgs(/*serverclass */);

};

}
