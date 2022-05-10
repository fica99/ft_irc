#include "main/precomp.h"

#include "server/commands/parsing/lexer/irclexer.h"

#include "server/commands/parsing/tokens/ircargtoken.h"
#include "server/commands/parsing/tokens/irccommandtoken.h"
#include "server/commands/parsing/tokens/ircprefixtoken.h"
#include "server/commands/parsing/tokens/irctokens.h"
#include "server/commands/parsing/ircparsinghelper.h"

namespace ircserv
{

IRCLexer::IRCLexer()
{
    Initialize();
}

void IRCLexer::Initialize(void)
{
}

IRCLexer::~IRCLexer()
{
    Shutdown();
}

void IRCLexer::Shutdown(void)
{
}

std::vector<IRCToken*> IRCLexer::Tokenize(const std::string& line)
{
    std::vector<IRCToken*> tokens;
    std::string msg = line;

    if (!msg.empty() && msg[0] == ':')
    {
        msg.erase(0, 1);
        tokens.push_back(GetPrefixToken(msg));
        if (msg.empty() || !IRCParsingHelper::IsSymbolSpace(msg[0]))
        {
            DestroyTokens(tokens);
            return tokens;
        }
        msg.erase(0, msg.find_first_not_of(IRCParsingHelper::IRCSymbolsDefinition::SPACE_ASCII));
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
    if (msg.size() != 2 || msg.compare(msg.size() - 2, 2, IRCParsingHelper::IRCSymbolsDefinition::CRLF_ASCII))
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
            m_TokensFactory.DestroyToken(tokens[i]);
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

    token = dynamic_cast<IRCPrefixToken*>(m_TokensFactory.CreateToken(Enum_IRCTokens_Prefix));
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

    pos = msg.find_first_not_of(IRCParsingHelper::IRCSymbolsDefinition::LETTERS_ASCII
        + IRCParsingHelper::IRCSymbolsDefinition::IRCSymbolsDefinition::DIGITS_ASCII
        + IRCParsingHelper::IRCSymbolsDefinition::IRCSymbolsDefinition::SPECIAL_ASCII);
    nick = msg.substr(0, pos);
    if (IRCParsingHelper::IsNick(nick))
    {
        msg.erase(0, pos);
    }
    else
    {
        nick.clear();
    }
    return nick;
}

std::string IRCLexer::GetUser(std::string& msg)
{
    std::string user;
    size_t pos;

    pos = msg.find_first_of("@ ");
    user = msg.substr(0, pos);
    if (IRCParsingHelper::IsUser(user))
    {
        msg.erase(0, pos);
    }
    else
    {
        user.clear();
    }
    return user;
}

std::string IRCLexer::GetHost(std::string& msg)
{
    std::string host;
    size_t pos;

    // add validation for host
    pos = msg.find_first_of(IRCParsingHelper::IRCSymbolsDefinition::SPACE_ASCII);
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

    pos = msg.find_first_of(IRCParsingHelper::IRCSymbolsDefinition::SPACE_ASCII);
    command = msg.substr(0, pos);
    if (IRCParsingHelper::IsLetterCommand(command))
    {
        msg.erase(0, pos);
    }
    else if (IRCParsingHelper::IsNumeriousCommand(command))
    {
        commandNumber = atoi(command.c_str());
        msg.erase(0, 3);
    }
    else
    {
        command.clear();
    }
    token = dynamic_cast<IRCCommandToken*>(m_TokensFactory.CreateToken(Enum_IRCTokens_Command));
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

    if (msg.empty() || !IRCParsingHelper::IsSymbolSpace(msg[0]))
    {
        return NULL;
    }
    pos = msg.find_first_not_of(IRCParsingHelper::IRCSymbolsDefinition::SPACE_ASCII);
    msg.erase(0, pos);
    if (!msg.empty())
    {
        if (msg[0] == ':')
        {
            msg.erase(0, 1);
            pos = msg.find(IRCParsingHelper::IRCSymbolsDefinition::CRLF_ASCII);
            arg = msg.substr(0, pos);
        }
        else
        {
            pos = msg.find_first_of(IRCParsingHelper::IRCSymbolsDefinition::WHITE_ASCII);
            arg = msg.substr(0, pos);
        }
        msg.erase(0, pos);
    }
    token = dynamic_cast<IRCArgToken*>(m_TokensFactory.CreateToken(Enum_IRCTokens_Arg));
    if (token != NULL)
    {
        token->SetArg(arg);
    }
    return token;
}

}




