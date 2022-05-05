#include "main/precomp.h"

#include "server/commands/parsing/parser/ircparser.h"

#include "server/commands/parsing/tokens/ircargtoken.h"
#include "server/commands/parsing/tokens/ircprefixtoken.h"

namespace ircserv
{

IRCParser::IRCParser()
{
    Initialize();
}

void IRCParser::Initialize(void)
{
}

IRCParser::~IRCParser()
{
    Shutdown();
}

void IRCParser::Shutdown(void)
{
}

IRCCommand* IRCParser::CreateCommand(const std::vector<IRCToken*>& tokens)
{
    IRCCommand* command = NULL;
    IRCPrefixToken* prefixToken = NULL;
    IRCCommandToken* commandToken = NULL;
    size_t i = 0;

    if (!tokens.empty())
    {
        prefixToken = dynamic_cast<IRCPrefixToken*>(tokens[i]);
        if (prefixToken != NULL)
        {
            ++i;
        }

        if (tokens.size() > i)
        {
            commandToken = dynamic_cast<IRCCommandToken*>(tokens[i++]);

            command = m_CommandsFactory.CreateCommand(GetCommandEnum(commandToken));
            if (command != NULL)
            {
                if (prefixToken != NULL)
                {
                    command->SetNick(prefixToken->GetNick());
                    command->SetUser(prefixToken->GetUser());
                    command->SetHost(prefixToken->GetHost());
                }
                command->SetArgs(GetArgs(std::vector<IRCToken*>(tokens.begin() + i, tokens.end())));
            }
        }

    }
    return command;
}

void IRCParser::DestroyCommand(IRCCommand* command)
{
    if (command != NULL)
    {
        m_CommandsFactory.DestroyCommand(command);
    }
}

Enum_IRCCommands IRCParser::GetCommandEnum(IRCCommandToken *commandToken)
{
    Enum_IRCCommands commandEnum = Enum_IRCCommands_Unknown;

    if (commandToken != NULL)
    {
        if (!EnumString<Enum_IRCCommands>::To(commandEnum, commandToken->GetCommand()))
        {
            commandEnum = static_cast<Enum_IRCCommands>(commandToken->GetCommandNumber());
        }
    }
    return commandEnum;
}

std::vector<std::string> IRCParser::GetArgs(const std::vector<IRCToken*>& tokens)
{
    std::vector<std::string> args;
    IRCArgToken* argToken;

    for (size_t i = 0; i < tokens.size(); ++i)
    {
        argToken = dynamic_cast<IRCArgToken*>(tokens[i]);
        if (argToken != NULL)
        {
            args.push_back(argToken->GetArg());
        }
    }
    return args;
}


}