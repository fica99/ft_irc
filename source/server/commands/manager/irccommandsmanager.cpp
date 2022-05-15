#include "main/precomp.h"

#include "server/commands/manager/irccommandsmanager.h"

#include "server/commands/commands/irccommand.h"
#include "server/commands/parsing/tokens/irctoken.h"
#include "server/commands/responses/ircresponsesfactory.h"
#include "server/Server.h"

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
    IRCResponsesFactory::CreateSingleton();
}

IRCCommandsManager::~IRCCommandsManager()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void IRCCommandsManager::Shutdown(void)
{
    IRCResponsesFactory::DestroySingleton();
}

void IRCCommandsManager::ProcessCommand(const std::string& message, Server *serv)
{
    IRC_PLOGD << "Processing message: " << message;
    std::vector<IRCToken*> tokens = m_Lexer.Tokenize(message);
    IRCCommand* command = m_Parser.CreateCommand(tokens);
    if (command != NULL)
    {
        IRC_PLOGI << "Got command from message: " << EnumString<Enum_IRCCommands>::From(command->GetCommandEnum()) << std::endl;
        command->ProcessCommand(serv);
    } else
    {
        IRC_PLOGE << "Invalid command from message: " << message << std::endl;
    }
    m_Lexer.DestroyTokens(tokens);
    m_Parser.DestroyCommand(command);
}

}
