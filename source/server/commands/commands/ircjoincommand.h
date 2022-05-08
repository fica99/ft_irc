#pragma once

#include <vector>
#include <string>

#include "server/commands/commands/irccommand.h"

namespace ircserv
{

class IRCJoinCommand : public IRCCommand
{
public:
    IRCJoinCommand();
    virtual ~IRCJoinCommand();
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
    inline void SetKeys(const std::vector<std::string>& keys) { m_Keys = keys; }

    std::vector<std::string> Split(std::string line, const std::string& delim);

private:
    std::vector<std::string> m_Channels;
    std::vector<std::string> m_Keys;
};

}
