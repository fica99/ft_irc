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
    bool ValidateArgs(IRCServer *serv);

private:
    inline void SetChannels(const std::vector<std::string>& channels) { m_Channels = channels; }
    const std::vector<std::string>& GetChannels(void) const { return m_Channels; }
    inline void SetKeys(const std::vector<std::string>& keys) { m_Keys = keys; }
    const std::vector<std::string>& GetKeys(void) const { return m_Keys; }

private:
    std::vector<std::string> m_Channels;
    std::vector<std::string> m_Keys;
};

}
