#pragma once

#include <string>
#include <sstream>
#include <vector>

#include "utils/singleton.h"
#include "ircmessages/tokens/irctoken.h"

namespace ircserv
{

struct IRCLexerParams
{
    std::string     prefix; // prefix for first part of message
    std::string     msgDelim; // delimeter between messages
    size_t          maxMsgLength; // max length of message
    std::string     tokensDelim; // delimeter between parts of messages
    std::string     blockDelim; // blocker for delimeter used for last long argument with spaces
};

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
    bool TokenizeNextMsg(std::istringstream& ss, std::vector<IRCToken*> tokens);
private:
    std::string ReadNextMsg(std::istringstream& ss);
    IRCToken* GetPrefixToken(std::string& msg);
    IRCToken* GetCommandToken(std::string& msg);
    IRCToken* GetArgumentToken(std::string& msg);

public:
    void SetLexerParams(const IRCLexerParams& params);
private:
    void ValidateLexerParams(const IRCLexerParams& params);

public:
    inline const IRCLexerParams& GetLexerParams(void) const { return m_LexerParams; }

private:
    IRCLexerParams m_LexerParams;
};

#define GetIRCLexer() IRCLexer::GetInstance()

}
