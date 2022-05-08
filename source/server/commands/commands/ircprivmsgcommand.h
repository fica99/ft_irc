#pragma once

#include "server/commands/commands/irccommand.h"

namespace ircserv
{

class IRCPrivmsgCommand : public IRCCommand
{
public:
    IRCPrivmsgCommand();
    virtual ~IRCPrivmsgCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(Server *serv);

private:
    bool ValidateArgs(/*serverclass */);
};

}
