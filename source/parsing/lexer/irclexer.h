#pragma once

#include <string>
#include <vector>

#include "parsing/tokens/irctoken.h"
#include "parsing/tokens/irctokensfactory.h"

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

public:
    std::vector<IRCToken*> Tokenize(std::string& msg);
    void DestroyTokens(std::vector<IRCToken*>& tokens);
private:
    IRCToken* GetPrefixToken(std::string& msg);
    std::string GetNick(std::string& msg);
    std::string GetUser(std::string& msg);
    std::string GetHost(std::string& msg);

    IRCToken* GetCommandToken(std::string& msg);
    IRCToken* GetArgToken(std::string& msg);
private:
    IRCTokensFactory m_TokensFactory;
};

}
