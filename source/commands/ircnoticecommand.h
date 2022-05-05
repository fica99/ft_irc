#pragma once

#include "commands/irccommand.h"

namespace ircserv
{

class IRCNoticeCommand : public IRCCommand
{
public:
    IRCNoticeCommand();
    virtual ~IRCNoticeCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(/*serverclass */);

private:
    bool ValidateArgs(/*serverclass */);

};

}
