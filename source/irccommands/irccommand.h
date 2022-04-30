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
    virtual bool ProcessCommand(/*serverclass */);

public:
    inline void SetCommandType(Enum_IRCCommands commandType) { m_CommandType = commandType; }
    inline Enum_IRCCommands GetCommandType(void) const { return m_CommandType; }
    inline void SetPrefix(const std::string& prefix) { m_Prefix = prefix; }
    inline const std::string& GetPrefix(void) const { return m_Prefix; }
    inline void SetArgs(const std::vector<std::string>& args) { m_Args = args; }
    inline const std::vector<std::string>& GetArgs(void) const { return m_Args; }

protected: 
    Enum_IRCCommands m_CommandType;
    std::string m_Prefix;
    std::vector<std::string> m_Args;
};

}
