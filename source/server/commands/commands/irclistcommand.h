#pragma once

#include "server/commands/commands/irccommand.h"

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
    bool ProcessCommand(Server *serv);

private:
    bool ValidateArgs(/*serverclass */);

};

}
