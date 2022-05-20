#include "main/precomp.h"

#include "managers/irccommandsmanager.h"

#include "irccommands/irccommand.h"
#include "parsing/tokens/irctoken.h"

namespace ircserv
{

IMPLEMENT_SIMPLE_SINGLETON(IRCCommandsManager);

IRCCommandsManager::IRCCommandsManager()
{
    IMPLEMENT_SIMPLE_SINGLETON_CONSTRUCTOR();

    Initialize();
}

void IRCCommandsManager::Initialize(void)
{
}

IRCCommandsManager::~IRCCommandsManager()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void IRCCommandsManager::Shutdown(void)
{
}

void IRCCommandsManager::ProcessCommand(const std::string& message)
{
    IRC_LOGD("Processing raw message: %s", message.c_str());
    std::vector<IRCToken*> tokens = m_Lexer.Tokenize(message);
    IRCCommand* command = m_Parser.CreateCommand(tokens);
    if (command != NULL)
    {
        IRC_LOGD("Got command from message: %s", EnumString<Enum_IRCCommands>::From(command->GetCommandEnum()).c_str());
        command->ProcessCommand();
    } else
    {
        IRC_LOGD("Invalid command message: %s", message.c_str());
    }
    m_Lexer.DestroyTokens(tokens);
    m_Parser.DestroyCommand(command);
}

}
