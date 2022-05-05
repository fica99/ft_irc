#include "main/precomp.h"

#include "commands/irccommandsfactory.h"

#include "utils/memory.h"
#include "commands/ircjoincommand.h"
#include "commands/irckickcommand.h"
#include "commands/irckillcommand.h"
#include "commands/irclistcommand.h"
#include "commands/ircnamescommand.h"
#include "commands/ircnickcommand.h"
#include "commands/ircnoticecommand.h"
#include "commands/ircopercommand.h"
#include "commands/ircpartcommand.h"
#include "commands/ircpasscommand.h"
#include "commands/ircprivmsgcommand.h"
#include "commands/ircquitcommand.h"
#include "commands/ircusercommand.h"

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
    IRCCommandsFactory::CreateSingleton();
}

IRCCommandsFactory::~IRCCommandsFactory()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void IRCCommandsFactory::Shutdown(void)
{
    IRCCommandsFactory::DestroySingleton();
}

IRCCommand* IRCCommandsFactory::CreateCommand(Enum_IRCCommands commandType)
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
        case Enum_IRCCommands_User:
            command = New(IRCUserCommand)();
            break;
        case Enum_IRCCommands_Oper:
            command = New(IRCOperCommand)();
            break;
        case Enum_IRCCommands_Quit:
            command = New(IRCQuitCommand)();
            break;
        case Enum_IRCCommands_Join:
            command = New(IRCJoinCommand)();
            break;
        case Enum_IRCCommands_Part:
            command = New(IRCPartCommand)();
            break;
        case Enum_IRCCommands_Names:
            command = New(IRCNamesCommand)();
            break;
        case Enum_IRCCommands_List:
            command = New(IRCListCommand)();
            break;
        case Enum_IRCCommands_Kick:
            command = New(IRCKickCommand)();
            break;
        case Enum_IRCCommands_Privmsg:
            command = New(IRCPrivmsgCommand)();
            break;
        case Enum_IRCCommands_Notice:
            command = New(IRCNoticeCommand)();
            break;
        case Enum_IRCCommands_Kill:
            command = New(IRCKillCommand)();
            break;
        default:
            command = NULL;
            break;
    }
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
