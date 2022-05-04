#pragma once

#include "irccommands/irccommand.h"

namespace ircserv
{

class IRCInviteCommand : public IRCCommand
{
public:
    IRCInviteCommand();
    virtual ~IRCInviteCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(/*serverclass */);

private:
    bool ValidateArgs(/*serverclass */);

};

}
