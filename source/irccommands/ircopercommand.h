#pragma once

#include <string>

#include "irccommands/irccommand.h"

namespace ircserv
{

class IRCOperCommand : public IRCCommand
{
public:
    IRCOperCommand();
    virtual ~IRCOperCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(IRCSocket *socket);

private:
    bool ValidateArgs(IRCSocket *socket);
private:
    bool IsOpersData(const std::string& user, const std::string& password) const;


private:
    inline void SetUser(const std::string& user) { m_User = user; }
    inline const std::string& GetUser(void) const { return m_User; }
    inline void SetPassword(const std::string& password) { m_Password = password; }
    inline const std::string& GetPassword(void) const { return m_Password; }

private:
    std::string m_User;
    std::string m_Password;
};

}
