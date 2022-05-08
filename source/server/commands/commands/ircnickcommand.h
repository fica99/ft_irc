#pragma once

#include "server/commands/commands/irccommand.h"

namespace ircserv
{

class IRCNickCommand : public IRCCommand
{
public:
    IRCNickCommand();
    virtual ~IRCNickCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(Server *serv);

private:
    bool ValidateArgs(/*serverclass */);

};

}
