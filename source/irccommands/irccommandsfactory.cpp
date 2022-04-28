#include "main/precomp.h"

#include "irccommands/irccommandsfactory.h"

#include "utils/memory.h"
#include "irccommands/ircpasscommand.h"
#include "irccommands/ircnickcommand.h"

namespace ircserv
{

IMPLEMENT_SIMPLE_SINGLETON(IRCCommandsFactory);

IRCCommandsFactory::IRCCommandsFactory()
{
    IMPLEMENT_SIMPLE_SINGLETON_CONSTRUCTOR();

    Initialize();
}

void IRCCommandsFactory::Initialize(void)
{
}

IRCCommandsFactory::~IRCCommandsFactory()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void IRCCommandsFactory::Shutdown(void)
{
}

IRCCommand* IRCCommandsFactory::CreateCommand(Enum_IRCCommands commandType,
                            const std::string& prefix,
                            const std::vector<std::string>& args)
{
    IRCCommand* command = NULL;
    switch (commandType)
    {
        case Enum_IRCCommands_Pass:
            command = New(IRCPassCommand)();
            break;
        case Enum_IRCCommands_Nick:
            command = New(IRCNickCommand)();
            break;
        default:
            command = New(IRCCommand)();
            break;
    }
    command->SetPrefix(prefix);
    command->SetArgs(args);
    return command;
}

void IRCCommandsFactory::DestroyCommand(IRCCommand* command)
{ 
    if (command != NULL)
    {
        Delete(command);
    }
}

}
