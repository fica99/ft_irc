#include "main/precomp.h"

#include "parsing/lexer/irclexer.h"

#include "parsing/tokens/ircargtoken.h"
#include "parsing/tokens/irccommandtoken.h"
#include "parsing/tokens/ircprefixtoken.h"
#include "parsing/tokens/irctokens.h"
#include "parsing/ircparsinghelper.h"

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
    IRCToken* token;
    std::string msg = line;
    static const size_t crlfLength = IRCParsingHelper::IRCSymbolsDefinition::CRLF_ASCII.size();

    if (msg.empty() || msg.size() > 512)
    {
        IRC_LOGD("Invalid message size: %d. Message should be greater then 0 and less then 512", msg.size());
        return tokens;
    }

    if (msg[0] == ':')
    {
        msg.erase(0, 1);
        
        token = GetPrefixToken(msg);
        if (token == NULL || msg.empty() || !IRCParsingHelper::IsSymbolSpace(msg[0]))
        {
            IRC_LOGD("%s", "Invalid prefix token in message. Expected space symbol after prefix");
            return tokens;
        }

        tokens.push_back(token);
        msg.erase(0, msg.find_first_not_of(IRCParsingHelper::IRCSymbolsDefinition::SPACE_ASCII));
    }

    token = GetCommandToken(msg);
    if (token == NULL)
    {
        IRC_LOGD("%s", "Invalid command token in message");
        DestroyTokens(tokens);
        return tokens;
    }
    tokens.push_back(token);

    while (msg.size() > crlfLength)
    {
        token = GetArgToken(msg);
        if (token == NULL)
        {
            IRC_LOGD("%s", "Invalid argument token in message");
            DestroyTokens(tokens);
            return tokens;
        }
        tokens.push_back(token);
    }

    if (msg.size() != crlfLength ||
        msg.compare(msg.size() - crlfLength, crlfLength, IRCParsingHelper::IRCSymbolsDefinition::CRLF_ASCII))
    {
        IRC_LOGD("%s", "No CRLF symbols at the end of message");
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
    if (nick.empty())
    {
        return NULL;
    }

    if (!msg.empty() && msg[0] == '!')
    {
        msg.erase(0, 1);
        user = GetUser(msg);
        if (user.empty())
        {
            return NULL;
        }
    }

    if (!msg.empty() && msg[0] == '@')
    {
        msg.erase(0, 1);
        host = GetHost(msg);
        if (host.empty())
        {
            return NULL;
        }
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
        IRC_LOGD("%s", "Invalid prefix nickname");
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
        IRC_LOGD("%s", "Invalid prefix username");
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

    pos = msg.find_first_not_of(IRCParsingHelper::IRCSymbolsDefinition::DIGITS_ASCII + IRCParsingHelper::IRCSymbolsDefinition::LETTERS_ASCII);
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

    if (command.empty() && !commandNumber)
    {
        IRC_LOGD("%s", "Command token is not numerious and not from letters");
        return NULL;
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
        IRC_LOGD("%s", "Before argument token should be space");
        return NULL;
    }
    pos = msg.find_first_not_of(IRCParsingHelper::IRCSymbolsDefinition::SPACE_ASCII);
    msg.erase(0, pos);

    if (!msg.empty() && msg[0] == ':')
    {
        msg.erase(0, 1);
        pos = msg.find(IRCParsingHelper::IRCSymbolsDefinition::CRLF_ASCII);
        arg = msg.substr(0, pos);
    }
    else
    {
        pos = msg.find_first_of(IRCParsingHelper::IRCSymbolsDefinition::WHITE_ASCII);
        arg = msg.substr(0, pos);
        if (arg.empty())
        {
            IRC_LOGD("%s", "Argument without colons cannot be empty");
            return NULL;
        }
    }
    msg.erase(0, pos);

    token = dynamic_cast<IRCArgToken*>(m_TokensFactory.CreateToken(Enum_IRCTokens_Arg));
    if (token != NULL)
    {
        token->SetArg(arg);
    }
    return token;
}

}




