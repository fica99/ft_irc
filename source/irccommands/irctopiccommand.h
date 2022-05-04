#pragma once

#include "irccommands/irccommand.h"

namespace ircserv
{

class IRCTopicCommand : public IRCCommand
{
public:
    IRCTopicCommand();
    virtual ~IRCTopicCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(/*serverclass */);

private:
    bool ValidateArgs(/*serverclass */);
};

}
