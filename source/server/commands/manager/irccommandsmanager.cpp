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
    std::vector<IRCToken*> tokens = m_Lexer.Tokenize(message);
    IRCCommand* command = m_Parser.CreateCommand(tokens);
    if (command != NULL)
    {
        command->ProcessCommand(serv);
    } else {
        std::cerr << "unknown command: " << message;
        if (*message.rbegin() != '\n')
            std::cerr << std::endl;
    }
    m_Lexer.DestroyTokens(tokens);
    m_Parser.DestroyCommand(command);
}

}
