#pragma once

#include <vector>
#include <string>

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
    bool ProcessCommand(IRCServer *serv);

private:
    bool ValidateArgs(IRCServer *serv);

private:
    inline void SetChannels(const std::vector<std::string>& channels) { m_Channels = channels; }

private:
    std::vector<std::string> m_Channels;
};

}
