#pragma once

#include <string>
#include <vector>

#include "utils/singleton.h"

#include "irccommands/irccommand.h"
#include "ircmessages/tokens/irctoken.h"

namespace ircserv
{

class IRCParser
{
public:
    IRCParser();
    virtual ~IRCParser();
private:
    void Initialize(void);
    void Shutdown(void);
    DECLARE_SIMPLE_SINGLETON(IRCParser);

public:
    IRCCommand* CreateCommand(const std::vector<IRCToken*>& tokens);
private:
    const std::string& GetPrefix(IRCToken* token); 
    Enum_IRCCommands GetCommand(IRCToken* token);
    std::vector<std::string> GetArgs(const std::vector<IRCToken*>& tokens);
};

#define GetIRCParser() IRCParser::GetInstance()

}
