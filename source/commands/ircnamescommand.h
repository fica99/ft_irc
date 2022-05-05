#pragma once

#include "commands/irccommand.h"

namespace ircserv
{

class IRCNamesCommand : public IRCCommand
{
public:
    IRCNamesCommand();
    virtual ~IRCNamesCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(/*serverclass */);

private:
    bool ValidateArgs(/*serverclass */);

};

}
