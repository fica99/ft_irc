#pragma once

#include "server/commands/commands/irccommand.h"

namespace ircserv
{

class IRCJoinCommand : public IRCCommand
{
public:
    IRCJoinCommand();
    virtual ~IRCJoinCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(Server *serv);

private:
    bool ValidateArgs(/*serverclass */);

};

}
