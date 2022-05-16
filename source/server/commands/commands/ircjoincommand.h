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
    bool ProcessCommand(IRCServer *serv);

private:
    bool ValidateArgs(/*serverclass */);

private:
    inline void SetChannels(const std::vector<std::string>& channels) { m_Channels = channels; }
    inline void SetKeys(const std::vector<std::string>& keys) { m_Keys = keys; }

private:
    std::vector<std::string> m_Channels;
    std::vector<std::string> m_Keys;
};

}
