#include "main/precomp.h"

#include "ircmessages/lexer/irclexer.h"

#include "ircmessages/tokens/irctokensfactory.h"

namespace ircserv
{

IMPLEMENT_SIMPLE_SINGLETON(IRCLexer);

IRCLexer::IRCLexer()
{
    IMPLEMENT_SIMPLE_SINGLETON_CONSTRUCTOR();

    Initialize();
}

void IRCLexer::Initialize(void)
{
    IRCTokensFactory::CreateSingleton();

    IRCLexerParams params =
    {
        .Prefix = ":",
        .TokensDelim = " ",
        .BlockDelim = ":"
    };
    SetLexerParams(params);
}

IRCLexer::~IRCLexer()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void IRCLexer::Shutdown(void)
{
    IRCTokensFactory::DestroySingleton();
}

std::vector<IRCToken*> IRCLexer::Tokenize(const std::string& line)
{
    std::vector<IRCToken*> tokens;
    IRCToken* token;
    std::string msg = line;

    token = GetPrefixToken(msg);
    if (token != NULL)
    {
        tokens.push_back(token);
    }

    token = GetCommandToken(msg);
    tokens.push_back(token);

    while (!msg.empty())
    {
        token = GetArgumentToken(msg);
        tokens.push_back(token);
    }
    return tokens;
}

IRCToken* IRCLexer::GetPrefixToken(std::string& msg)
{
    IRCToken* token = NULL;
    size_t pos = 0;

    pos = msg.find(m_LexerParams.TokensDelim);
    if (!msg.compare(0, m_LexerParams.Prefix.size(), m_LexerParams.Prefix))
    {
        token = GetIRCTokensFactory().CreatePrefixToken(msg.substr(0, pos), m_LexerParams.Prefix);
        msg.erase(0, msg.find_first_not_of(m_LexerParams.TokensDelim, pos));
    }
    return token;
}

IRCToken* IRCLexer::GetCommandToken(std::string& msg)
{
    IRCToken* token = NULL;
    size_t pos = 0;

    pos = msg.find(m_LexerParams.TokensDelim);
    token = GetIRCTokensFactory().CreateCommandToken(msg.substr(0, pos));
    msg.erase(0, msg.find_first_not_of(m_LexerParams.TokensDelim, pos));
    return token;
}

IRCToken* IRCLexer::GetArgumentToken(std::string& msg)
{
    IRCToken* token = NULL;
    size_t pos = 0;

    if (!msg.compare(0, m_LexerParams.BlockDelim.size(), m_LexerParams.BlockDelim))
    {
        msg.erase(0, m_LexerParams.BlockDelim.size());
        pos = msg.size();
    }
    else
    {
        pos = msg.find(m_LexerParams.TokensDelim);
    }
    token = GetIRCTokensFactory().CreateToken(msg.substr(0, pos));
    msg.erase(0, msg.find_first_not_of(m_LexerParams.TokensDelim, pos));
    return token;
}


void IRCLexer::SetLexerParams(const IRCLexerParams& params)
{
    ValidateLexerParams(params);
    m_LexerParams = params;
}

void IRCLexer::ValidateLexerParams(const IRCLexerParams& params)
{
    if (params.TokensDelim.empty())
    {
        throw std::invalid_argument("Invalid delimeter between tokens!");
    }
}






}




