#include "main/precomp.h"

#include "managers/irccommandsmanager.h"

#include "irccommands/irccommand.h"
#include "irccommands/irccommandsfactory.h"
#include "irccommands/irccommandshelper.h"
#include "ircresponses/ircresponseshelper.h"
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
}

IRCCommandsManager::~IRCCommandsManager()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void IRCCommandsManager::Shutdown(void)
{
}

static void ProcessCommand(IRCCommand *command, IRCSocket *socket, const std::string& message)
{
    if (command != NULL)
    {
        command->ProcessCommand(socket);
    }
    else
    {
        if (IRCCommandsHelper::IsRegistered(socket))
        {
            IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_UNKNOWNCOMMAND, message);
        }
    }
}

void IRCCommandsManager::ProcessCommands(std::string message, IRCSocket *socket)
{
    std::vector<std::string> messages;
    IRCCommand* command;

    IRC_LOGD("Processing raw message: %s", message.c_str());

    if (message.empty())
    {
        ProcessCommands("QUIT\r\n", socket);
        return;
    }
    if (message.find(IRCParsingHelper::IRCSymbolsDefinition::CRLF_ASCII) != message.npos)
    {
        messages = IRCParsingHelper::Split(message, IRCParsingHelper::IRCSymbolsDefinition::CRLF_ASCII);
    }
    else if (message.find(IRCParsingHelper::IRCSymbolsDefinition::LF_ASCII) != message.npos)
    {
        messages = IRCParsingHelper::Split(message, IRCParsingHelper::IRCSymbolsDefinition::LF_ASCII);
    }

    for (size_t i = 0; i < messages.size(); ++i)
    {
        std::vector<IRCToken*> tokens = m_Lexer.Tokenize(messages[i]);
        command = m_Parser.CreateCommand(tokens);
        ProcessCommand(command, socket, messages[i]);
        m_Lexer.DestroyTokens(tokens);
        IRCCommandsFactory::DestroyCommand(command);
    }
}

}
