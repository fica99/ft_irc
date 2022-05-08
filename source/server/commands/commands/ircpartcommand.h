#pragma once

#include "server/commands/commands/irccommand.h"

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
    bool ProcessCommand(Server *serv);

private:
    bool ValidateArgs(/*serverclass */);
};

}
