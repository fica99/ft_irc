#pragma once

#include "utils/singleton.h"

#include "server/commands/parsing/lexer/irclexer.h"
#include "server/commands/parsing/parser/ircparser.h"

namespace ircserv
{

class IRCCommandsManager
{
public:
    IRCCommandsManager();
    virtual ~IRCCommandsManager();
private:
    void Initialize(void);
    void Shutdown(void);
    DECLARE_SIMPLE_SINGLETON(IRCCommandsManager);

public:
    void ProcessCommand(const std::string& message, Server *serv);
private:
    IRCLexer m_Lexer;
    IRCParser m_Parser;
};

#define GetIRCCommandsManager() IRCCommandsManager::GetInstance()


}
