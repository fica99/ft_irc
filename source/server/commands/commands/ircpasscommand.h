#pragma once

#include "server/commands/commands/irccommand.h"

namespace ircserv
{

class IRCPassCommand : public IRCCommand
{
public:
    IRCPassCommand();
    virtual ~IRCPassCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(Server *serv);

private:
    bool ValidateArgs(/*serverclass */);
};

}
