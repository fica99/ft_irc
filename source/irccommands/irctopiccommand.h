#pragma once

#include <string>

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
    bool ProcessCommand(IRCSocket *socket);

private:
    bool ValidateArgs(IRCSocket *socket);

private:
    inline void SetChannel(const std::string& channel) { m_Channel = channel; }
    inline const std::string& GetChannel(void) const { return m_Channel; }
    inline void SetTopic(const std::string& topic) { m_Topic = topic; }
    inline const std::string& GetTopic(void) const { return m_Topic; }
private:
    std::string m_Channel;
    std::string m_Topic;
};

}
