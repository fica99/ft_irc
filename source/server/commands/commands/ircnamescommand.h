#pragma once

#include "server/commands/commands/irccommand.h"

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
    bool ProcessCommand(Server *serv);

private:
    bool ValidateArgs(/*serverclass */);

};

}
