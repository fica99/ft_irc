#pragma once

#include "irccommands/irccommand.h"
#include "server/Server.h"

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
    bool ProcessCommand(Server *s, std::pair<const int, Client> client);
};

}
