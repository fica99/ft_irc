#pragma once

#include <string>

#include "irccommands/irccommand.h"

namespace ircserv
{

class IRCKillCommand : public IRCCommand
{
public:
    IRCKillCommand();
    virtual ~IRCKillCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(IRCSocket *socket);

private:
    bool ValidateArgs(void);

private:
    inline void SetNickname(const std::string& nickname) { m_Nickname = nickname; }
    inline void SetComment(const std::string& comment) { m_Comment = comment; }
private:
    std::string m_Nickname;
    std::string m_Comment;

};

}
