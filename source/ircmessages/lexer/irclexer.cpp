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
        .prefix = ":",
        .msgDelim = "\r\n",
        .maxMsgLength = 512,
        .tokensDelim = " ",
        .blockDelim = ":"
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

std::vector<IRCToken*> IRCLexer::TokenizeNextMsg(std::istringstream& ss)
{
    std::vector<IRCToken*> tokens;
    std::string msg;
    IRCToken* token;

    msg = ReadNextMsg(ss);
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

std::string IRCLexer::ReadNextMsg(std::istringstream& ss)
{
    std::string msg;
    size_t readedSymbCounter;

    readedSymbCounter = 0;
    msg.reserve(m_LexerParams.maxMsgLength);
    while (readedSymbCounter < m_LexerParams.maxMsgLength)
    {
        ss.getline(&(msg[readedSymbCounter]), m_LexerParams.maxMsgLength - readedSymbCounter, m_LexerParams.msgDelim[m_LexerParams.msgDelim.size() - 1]);
        readedSymbCounter += ss.gcount();
        if (readedSymbCounter < m_LexerParams.msgDelim.size())
        {
            continue;
        }
        if (!msg.compare(
            readedSymbCounter - m_LexerParams.msgDelim.size(),
            readedSymbCounter, m_LexerParams.msgDelim))
        {
            break;
        }
        else
        {
            msg.push_back(m_LexerParams.msgDelim[m_LexerParams.msgDelim.size() - 1]);
        }
    }
    return msg;
}

IRCToken* IRCLexer::GetPrefixToken(std::string& msg)
{
    IRCToken* token = NULL;
    size_t pos = 0;

    pos = msg.find(m_LexerParams.tokensDelim);
    try
    {
        token = GetIRCTokensFactory().CreatePrefixToken(msg.substr(0, pos), m_LexerParams.prefix);
    }
    catch (const std::invalid_argument &x)
    {
        token = NULL;
    }
    msg.erase(0, msg.find_first_not_of(m_LexerParams.tokensDelim, pos));
    return token;
}

IRCToken* IRCLexer::GetCommandToken(std::string& msg)
{
    IRCToken* token = NULL;
    size_t pos = 0;

    pos = msg.find(m_LexerParams.tokensDelim);
    token = GetIRCTokensFactory().CreateCommandToken(msg.substr(0, pos));
    msg.erase(0, msg.find_first_not_of(m_LexerParams.tokensDelim, pos));
    return token;
}

IRCToken* IRCLexer::GetArgumentToken(std::string& msg)
{
    IRCToken* token = NULL;
    size_t pos = 0;

    if (!msg.compare(0, m_LexerParams.blockDelim.size(), m_LexerParams.blockDelim))
    {
        msg.erase(0);
        pos = msg.size();
    }
    else
    {
        pos = msg.find(m_LexerParams.tokensDelim);
    }
    token = GetIRCTokensFactory().CreateToken(msg.substr(0, pos));
    msg.erase(0, msg.find_first_not_of(m_LexerParams.tokensDelim, pos));
    return token;
}


void IRCLexer::SetLexerParams(const IRCLexerParams& params)
{
    ValidateLexerParams(params);
    m_LexerParams = params;
}

void IRCLexer::ValidateLexerParams(const IRCLexerParams& params)
{
    if (params.msgDelim.empty())
    {
        throw std::invalid_argument("Invalid delimeter between messages!");
    }
    if (params.maxMsgLength == 0)
    {
        throw std::invalid_argument("Invalid max message length!");
    }
    if (params.tokensDelim.empty())
    {
        throw std::invalid_argument("Invalid delimeter between tokens!");
    }
}






}




