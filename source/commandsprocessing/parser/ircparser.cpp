#include "main/precomp.h"

#include "commandsprocessing/parser/ircparser.h"

#include "commandsprocessing/tokens/ircargtoken.h"
#include "commands/irccommandsfactory.h"
#include "commandsprocessing/tokens/ircprefixtoken.h"

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

            command = GetIRCCommandsFactory().CreateCommand(GetCommandEnum(commandToken));
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
        GetIRCCommandsFactory().DestroyCommand(command);
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
