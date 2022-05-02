#pragma once

#include <string>
#include <vector>

#include "utils/singleton.h"
#include "ircmessages/tokens/irctoken.h"

namespace ircserv
{

class IRCLexer
{
public:
    IRCLexer();
    virtual ~IRCLexer();
private:
    void Initialize(void);
    void Shutdown(void);
    DECLARE_SIMPLE_SINGLETON(IRCLexer);

public:
    std::vector<IRCToken*> Tokenize(const std::string& line);
    void DestroyTokens(std::vector<IRCToken*>& tokens);
private:
    IRCToken* GetPrefixToken(std::string& msg);
    std::string GetNick(std::string& msg);
    std::string GetUser(std::string& msg);
    std::string GetHost(std::string& msg);

    IRCToken* GetCommandToken(std::string& msg);
    IRCToken* GetArgumentToken(std::string& msg);
private:
    const std::string LETTERS;
    const std::string DIGITS;
    const std::string SPECIAL;
    const std::string WHITE;

};

#define GetIRCLexer() IRCLexer::GetInstance()

}
