#include "main/precomp.h"

#include "ircmessages/parser/ircparser.h"

#include "irccommands/irccommandsfactory.h"
#include "ircmessages/tokens/ircprefixtoken.h"
#include "ircmessages/tokens/irccommandtoken.h"

namespace ircserv
{

IMPLEMENT_SIMPLE_SINGLETON(IRCParser);

IRCParser::IRCParser()
{
    IMPLEMENT_SIMPLE_SINGLETON_CONSTRUCTOR();

    Initialize();
}

void IRCParser::Initialize(void)
{
    IRCCommandsFactory::CreateSingleton();
}

IRCParser::~IRCParser()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void IRCParser::Shutdown(void)
{
    IRCCommandsFactory::DestroySingleton();
}

IRCCommand* IRCParser::CreateCommand(const std::vector<IRCToken*>& tokens)
{
    IRCCommand* command = NULL;
    if (tokens.empty())
    {
        command = GetIRCCommandsFactory().CreateCommand();
    }
    else
    {
        const std::string& prefix = GetPrefix(tokens[0]);
        if (tokens.size() == 1)
        {
            command = GetIRCCommandsFactory().CreateCommand(Enum_IRCCommands_Unknown, prefix);
        }
        else
        {
            command = GetIRCCommandsFactory().CreateCommand(
                GetCommand(tokens[1]),
                prefix,
                GetArgs(std::vector<IRCToken*>(tokens.begin() + 2, tokens.end()))
            );
        }
    }
    return command;
}

const std::string& IRCParser::GetPrefix(IRCToken* token)
{
    static const std::string empty = "";

    if (token == NULL || !dynamic_cast<IRCPrefixToken*>(token))
    {
        return empty;
    }
    IRCPrefixToken* prefixToken = dynamic_cast<IRCPrefixToken*>(token);
    return prefixToken->GetProcessedStr();
}

Enum_IRCCommands IRCParser::GetCommand(IRCToken* token)
{
    if (token == NULL || !dynamic_cast<IRCCommandToken*>(token))
    {
        return Enum_IRCCommands_Unknown;
    }
    IRCCommandToken* commandToken = dynamic_cast<IRCCommandToken*>(token);
    return commandToken->GetCommandEnum();
}

std::vector<std::string> IRCParser::GetArgs(const std::vector<IRCToken*>& tokens)
{
    std::vector<std::string> args;
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        args.push_back(tokens[i]->GetRawStr());
    }
    return args;
}



}
