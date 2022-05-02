#pragma once

#include <string>
#include <vector>

#include "irccommands/irccommands.h"

namespace ircserv
{

class IRCCommand
{
public:
    IRCCommand();
    virtual ~IRCCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    virtual bool ProcessCommand(/*serverclass */) = 0;

public:
    inline void SetNick(const std::string& nick) { m_Nick = nick; }
    inline void SetUser(const std::string& user) { m_User = user; }
    inline void SetHost(const std::string& host) { m_Host = host; }
    inline void SetArgs(const std::vector<std::string>& args) { m_Args = args; }
    inline const std::vector<std::string>& GetArgs(void) const { return m_Args; }

protected: 
    std::string m_Nick;
    std::string m_User;
    std::string m_Host;
    std::vector<std::string> m_Args;
};

}
