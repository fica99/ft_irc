#include "main/precomp.h"

#include "commandsprocessing/lexer/irclexer.h"

#include "commandsprocessing/tokens/irctokens.h"
#include "commandsprocessing/tokens/ircprefixtoken.h"
#include "commandsprocessing/tokens/irccommandtoken.h"
#include "commandsprocessing/tokens/ircargtoken.h"
#include "commandsprocessing/tokens/irctokensfactory.h"

namespace ircserv
{

IMPLEMENT_SIMPLE_SINGLETON(IRCLexer);

IRCLexer::IRCLexer()
    : LETTERS_ASCII("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz")
    , DIGITS_ASCII("0123456789")
    , SPECIAL_ASCII("-[]\\`/^{}")
    , WHITE_ASCII(" \a\0\r\n,")
{
    IMPLEMENT_SIMPLE_SINGLETON_CONSTRUCTOR();

    Initialize();
}

void IRCLexer::Initialize(void)
{
    IRCTokensFactory::CreateSingleton();
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
    std::string msg = line;

    if (!msg.empty() && msg[0] == ':')
    {
        msg.erase(0, 1);
        tokens.push_back(GetPrefixToken(msg));
        msg.erase(0, msg.find_first_not_of(' '));
    }

    tokens.push_back(GetCommandToken(msg));

    while (msg.size() > 2)
    {
        tokens.push_back(GetArgToken(msg));
        if (tokens.back() == NULL)
        {
            break;
        }
    }
    if (msg.size() != 2 || msg.compare(msg.size() - 2, 2, "\r\n"))
    {
        DestroyTokens(tokens);
    }    
    return tokens;
}

void IRCLexer::DestroyTokens(std::vector<IRCToken*>& tokens)
{
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        if (tokens[i])
        {
            GetIRCTokensFactory().DestroyToken(tokens[i]);
        }
    }
    tokens.clear();
}


IRCToken* IRCLexer::GetPrefixToken(std::string& msg)
{
    IRCPrefixToken* token;
    std::string nick;
    std::string user;
    std::string host;

    nick = GetNick(msg);
    if (!msg.empty() && msg[0] == '!')
    {
        msg.erase(0, 1);
        user = GetUser(msg);
    }
    if (!msg.empty() && msg[0] == '@')
    {
        msg.erase(0, 1);
        host = GetHost(msg);
    }

    token = dynamic_cast<IRCPrefixToken*>(GetIRCTokensFactory().CreateToken(Enum_IRCTokens_Prefix));
    if (token != NULL)
    {
        token->SetNick(nick);
        token->SetUser(user);
        token->SetHost(host);
    }
    return token;
}

std::string IRCLexer::GetNick(std::string& msg)
{
    std::string nick;
    size_t pos;

    pos = msg.find_first_not_of(LETTERS_ASCII + DIGITS_ASCII + SPECIAL_ASCII);
    nick = msg.substr(0, pos);
    msg.erase(0, pos);
    return nick;
}

std::string IRCLexer::GetUser(std::string& msg)
{
    std::string user;
    size_t pos;

    pos = msg.find_first_of(WHITE_ASCII + "@");
    user = msg.substr(0, pos);
    msg.erase(0, pos);
    return user;
}

std::string IRCLexer::GetHost(std::string& msg)
{
    std::string host;
    size_t pos;

    // add validation for host
    pos = msg.find_first_of(" ");
    host = msg.substr(0, pos);
    msg.erase(0, pos);
    return host;
}

IRCToken* IRCLexer::GetCommandToken(std::string& msg)
{
    IRCCommandToken* token;
    size_t pos;
    std::string command;
    unsigned short int commandNumber = 0;

    pos = msg.find_first_not_of(LETTERS_ASCII);
    if (pos != 0)
    {
        command = msg.substr(0, pos);
        msg.erase(0, pos);
    }
    else if (msg.size() >= 3 && DIGITS_ASCII.find(msg[0]) != DIGITS_ASCII.npos
            && DIGITS_ASCII.find(msg[1]) != DIGITS_ASCII.npos
            && DIGITS_ASCII.find(msg[2]) != DIGITS_ASCII.npos)
    {
        commandNumber = atoi(msg.substr(0, 3).c_str());
        msg.erase(0, 3);
    }
    token = dynamic_cast<IRCCommandToken*>(GetIRCTokensFactory().CreateToken(Enum_IRCTokens_Command));
    if (token != NULL)
    {
        token->SetCommand(command);
        token->SetCommandNumber(commandNumber);
    }
    return token;
}

IRCToken* IRCLexer::GetArgToken(std::string& msg)
{
    IRCArgToken* token;
    size_t pos;
    std::string arg;

    if (msg.empty() || msg[0] != ' ')
    {
        return NULL;
    }
    pos = msg.find_first_not_of(' ');
    msg.erase(0, pos);
    if (!msg.empty())
    {
        if (msg[0] == ':')
        {
            msg.erase(0, 1);
            pos = msg.find_first_of("\r\n\0");
            arg = msg.substr(0, pos);
        }
        else
        {
            pos = msg.find_first_of(" \r\n\0");
            arg = msg.substr(0, pos);
        }
        msg.erase(0, pos);
    }
    token = dynamic_cast<IRCArgToken*>(GetIRCTokensFactory().CreateToken(Enum_IRCTokens_Arg));
    if (token != NULL)
    {
        token->SetArg(arg);
    }
    return token;
}

}




