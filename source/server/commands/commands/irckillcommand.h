#pragma once

#include "server/commands/commands/irccommand.h"

namespace ircserv
{

class IRCKillCommand : public IRCCommand
{
public:
    IRCKillCommand();
    virtual ~IRCKillCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(/*serverclass */);

private:
    bool ValidateArgs(/*serverclass */);

};

}
