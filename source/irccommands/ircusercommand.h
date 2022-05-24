#pragma once

#include <string>

#include "irccommands/irccommand.h"

namespace ircserv
{

class IRCUserCommand : public IRCCommand
{
public:
    IRCUserCommand();
    virtual ~IRCUserCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(IRCSocket *socket);

private:
    bool ValidateArgs(void);

private:
    inline void SetUsername(const std::string& username) { m_Username = username; }
    inline const std::string& GetUsername(void) const { return m_Username; }
    inline void SetRealname(const std::string& realname) { m_Realname = realname; }
    inline const std::string& GetRealname(void) const { return m_Realname; }
private:
    std::string m_Username;
    std::string m_Realname;
};

}
