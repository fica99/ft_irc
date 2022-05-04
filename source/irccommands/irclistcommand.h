#pragma once

#include "irccommands/irccommand.h"

namespace ircserv
{

class IRCListCommand : public IRCCommand
{
public:
    IRCListCommand();
    virtual ~IRCListCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(/*serverclass */);

private:
    bool ValidateArgs(/*serverclass */);

};

}
