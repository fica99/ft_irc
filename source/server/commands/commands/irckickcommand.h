#pragma once

#include <string>

#include "server/commands/commands/irccommand.h"

namespace ircserv
{

class IRCKickCommand : public IRCCommand
{
public:
    IRCKickCommand();
    virtual ~IRCKickCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(IRCServer *serv);

private:
    bool ValidateArgs(IRCServer *serv);

private:
    inline void SetChannel(const std::string& channel) { m_Channel = channel; }
    inline void SetUser(const std::string& user) { m_User = user; }
    inline void SetComment(const std::string& comment) { m_Comment = comment; }

private:
    std::string m_Channel;
    std::string m_User;
    std::string m_Comment;
};

}