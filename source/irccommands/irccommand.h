#pragma once

#include <string>
#include <vector>

#include "irccommands/irccommands.h"

namespace ircserv
{

class IRCSocket;
class IRCCommand
{
public:
    IRCCommand(Enum_IRCCommands commandEnum);
    virtual ~IRCCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    virtual bool ProcessCommand(IRCSocket *socket) = 0;

private:
    virtual bool ValidateArgs(IRCSocket *socket) = 0;

public:
    inline void SetCommandEnum(Enum_IRCCommands commandEnum) { m_CommandEnum = commandEnum; }
    inline Enum_IRCCommands GetCommandEnum(void) const { return m_CommandEnum; }
    inline void SetPrefixNick(const std::string& nick) { m_PrefixNick = nick; }
    inline const std::string& GetPrefixNick(void) const { return m_PrefixNick; }
    inline void SetPrefixUser(const std::string& user) { m_PrefixUser = user; }
    inline const std::string& GetPrefixUser(void) const { return m_PrefixUser; }
    inline void SetPrefixHost(const std::string& host) { m_PrefixHost = host; }
    inline const std::string& GetPrefixHost(void) const { return m_PrefixHost; }
    inline void SetArgs(const std::vector<std::string>& args) { m_Args = args; }
    inline const std::vector<std::string>& GetArgs(void) const { return m_Args; }

private:
    Enum_IRCCommands m_CommandEnum;
    std::string m_PrefixNick;
    std::string m_PrefixUser;
    std::string m_PrefixHost;
    std::vector<std::string> m_Args;
};

}
