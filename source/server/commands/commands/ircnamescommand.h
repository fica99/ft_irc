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
    bool ProcessCommand(/*serverclass */);

private:
    bool ValidateArgs(/*serverclass */);

private:
    bool SetChannels(const std::string& channels);
    bool SetChannel(const std::string& channel);

private:
    std::vector<std::string> m_Channels;
};

}
