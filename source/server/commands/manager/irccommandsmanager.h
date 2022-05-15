#pragma once

#include "server/commands/parsing/lexer/irclexer.h"
#include "server/commands/parsing/parser/ircparser.h"

namespace ircserv
{

class IRCServer;

class IRCCommandsManager
{
public:
    IRCCommandsManager();
    virtual ~IRCCommandsManager();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    void ProcessCommand(const std::string& message, IRCServer *serv);
private:
    IRCLexer m_Lexer;
    IRCParser m_Parser;
};

}
