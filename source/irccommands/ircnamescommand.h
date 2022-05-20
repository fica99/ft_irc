#pragma once

#include <vector>
#include <string>

#include "irccommands/irccommand.h"

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
    bool ProcessCommand(void);

private:
    bool ValidateArgs(void);

private:
    inline void SetChannels(const std::vector<std::string>& channels) { m_Channels = channels; }

private:
    std::vector<std::string> m_Channels;
};

}
