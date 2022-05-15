#include "main/precomp.h"

#include "server/commands/manager/irccommandsmanager.h"

#include "server/commands/commands/irccommand.h"
#include "server/commands/parsing/tokens/irctoken.h"
#include "server/commands/responses/ircresponsesfactory.h"

namespace ircserv
{

IRCCommandsManager::IRCCommandsManager()
{
    Initialize();
}

void IRCCommandsManager::Initialize(void)
{
    IRCResponsesFactory::CreateSingleton();
}

IRCCommandsManager::~IRCCommandsManager()
{
    Shutdown();
}

void IRCCommandsManager::Shutdown(void)
{
    IRCResponsesFactory::DestroySingleton();
}

void IRCCommandsManager::ProcessCommand(const std::string& message, IRCServer *serv)
{
    IRC_LOGD("Processing message: %s", message.c_str());
    std::vector<IRCToken*> tokens = m_Lexer.Tokenize(message);
    IRCCommand* command = m_Parser.CreateCommand(tokens);
    if (command != NULL)
    {
        IRC_LOGD("Got command from message: %s", EnumString<Enum_IRCCommands>::From(command->GetCommandEnum()).c_str());
        command->ProcessCommand(serv);
    } else
    {
        IRC_LOGD("Invalid command message: %s", message.c_str());
    }
    m_Lexer.DestroyTokens(tokens);
    m_Parser.DestroyCommand(command);
}

}
