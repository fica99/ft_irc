#pragma once

#include "server/commands/commands/irccommand.h"

namespace ircserv
{

class IRCOperCommand : public IRCCommand
{
public:
    IRCOperCommand();
    virtual ~IRCOperCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(Server *serv);

private:
    bool ValidateArgs(/*serverclass */);
};

}
