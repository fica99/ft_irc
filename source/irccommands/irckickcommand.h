#pragma once

#include <string>

#include "irccommands/irccommand.h"

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
    bool ProcessCommand(IRCSocket *socket);

private:
    bool ValidateArgs(IRCSocket *socket);

private:
    inline void SetChannel(const std::string& channel) { m_Channel = channel; }
    inline const std::string& GetChannel(void) const { return m_Channel; }
    inline void SetUser(const std::string& user) { m_User = user; }
    inline const std::string& GetUser(void) const { return m_User; }
    inline void SetComment(const std::string& comment) { m_Comment = comment; }
    inline const std::string& GetComment(void) const { return m_Comment; }

private:
    std::string m_Channel;
    std::string m_User;
    std::string m_Comment;
};

}
