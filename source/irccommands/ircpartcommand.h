#pragma once

#include <vector>
#include <string>

#include "irccommands/irccommand.h"

namespace ircserv
{

class IRCPartCommand : public IRCCommand
{
public:
    IRCPartCommand();
    virtual ~IRCPartCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(IRCSocket *socket);

private:
    bool ValidateArgs(IRCSocket *socket);

private:
    inline void SetChannels(const std::vector<std::string>& channels) { m_Channels = channels; }
    inline const std::vector<std::string>& GetChannels(void) const { return m_Channels; }

private:
    std::vector<std::string> m_Channels;
};

}
