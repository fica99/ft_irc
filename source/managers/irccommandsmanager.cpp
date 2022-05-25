#include "main/precomp.h"

#include "managers/irccommandsmanager.h"

#include "irccommands/irccommand.h"
#include "ircserver/ircserver.h"
#include "managers/ircclientsmanager.h"
#include "parsing/tokens/irctoken.h"
#include "parsing/ircparsinghelper.h"

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
    IRCClientsManager::CreateSingleton();
}

IRCCommandsManager::~IRCCommandsManager()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void IRCCommandsManager::Shutdown(void)
{
    IRCClientsManager::DestroySingleton();
}

static void EraseClient(IRCSocket *socket)
{
    IRC_LOGI("%s", "Received closing connection with client");
    GetIRCClientsManager().EraseClient(socket);
    GetIRCServer().CloseConnection(socket);
}

void IRCCommandsManager::ProcessCommand(std::string message, IRCSocket *socket)
{
    std::vector<std::string> messages;


    IRC_LOGD("Processing raw message: %s", message.c_str());
    messages = IRCParsingHelper::Split(message, IRCParsingHelper::IRCSymbolsDefinition::CRLF_ASCII);
    if (message.empty())
    {
        EraseClient(socket);
        return;
    }
    for (size_t i = 0; i < messages.size(); ++i)
    {
        IRC_LOGD("Processing splitted message: %s", messages[i].c_str());
        std::vector<IRCToken*> tokens = m_Lexer.Tokenize(messages[i]);
        IRCCommand* command = m_Parser.CreateCommand(tokens);
        if (command != NULL)
        {
            IRC_LOGD("Received command: %s", EnumString<Enum_IRCCommands>::From(command->GetCommandEnum()).c_str());
            command->ProcessCommand(socket);
        } else
        {
            IRC_LOGI("%s", "Unknown command received");
        }
        m_Lexer.DestroyTokens(tokens);
        m_Parser.DestroyCommand(command);
    }
}

}
