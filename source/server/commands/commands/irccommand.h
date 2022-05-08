#pragma once

#include <string>
#include <vector>

#include "server/commands/commands/irccommands.h"

namespace ircserv
{

class IRCCommand
{
public:
    IRCCommand(Enum_IRCCommands commandEnum = Enum_IRCCommands_Unknown);
    virtual ~IRCCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    virtual bool ProcessCommand(/*serverclass */) = 0;

private:
    virtual bool ValidateArgs(/*serverclass */) = 0;

public:
    inline void SetPrefixNick(const std::string& nick) { m_PrefixNick = nick; }
    inline void SetPrefixUser(const std::string& user) { m_PrefixUser = user; }
    inline void SetPrefixHost(const std::string& host) { m_PrefixHost = host; }
    inline void SetArgs(const std::vector<std::string>& args) { m_Args = args; }
    inline const std::vector<std::string>& GetArgs(void) const { return m_Args; }

protected:
    inline Enum_IRCCommands GetCommandEnum(void) const { return m_CommandEnum; }
private:
    Enum_IRCCommands m_CommandEnum;
protected: 
    std::string m_PrefixNick;
    std::string m_PrefixUser;
    std::string m_PrefixHost;
    std::vector<std::string> m_Args;
};

}
