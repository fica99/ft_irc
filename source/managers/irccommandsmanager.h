#pragma once

#include "ircresponses/ircresponsesfactory.h"
#include "parsing/lexer/irclexer.h"
#include "parsing/parser/ircparser.h"
#include "utils/singleton.h"

namespace ircserv
{

class IRCSocket;

class IRCCommandsManager
{
public:
    IRCCommandsManager();
    virtual ~IRCCommandsManager();
    DECLARE_SIMPLE_SINGLETON(IRCCommandsManager);
private:
    void Initialize(void);
    void Shutdown(void);

public:
    void ProcessCommand(std::string message, IRCSocket *socket);
private:
    IRCLexer m_Lexer;
    IRCParser m_Parser;
    IRCResponsesFactory m_ResponsesFactory;
};

#define GetIRCCommandsManager() IRCCommandsManager::GetInstance()

}
