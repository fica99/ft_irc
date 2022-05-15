#include "main/precomp.h"

#include "server/commands/commands/irccommandsfactory.h"

#include "utils/memory.h"
#include "server/commands/commands/irccommand.h"
#include "server/commands/commands/ircjoincommand.h"
#include "server/commands/commands/irckickcommand.h"
#include "server/commands/commands/irckillcommand.h"
#include "server/commands/commands/irclistcommand.h"
#include "server/commands/commands/ircnamescommand.h"
#include "server/commands/commands/ircnickcommand.h"
#include "server/commands/commands/ircnoticecommand.h"
#include "server/commands/commands/ircopercommand.h"
#include "server/commands/commands/ircpartcommand.h"
#include "server/commands/commands/ircpasscommand.h"
#include "server/commands/commands/ircprivmsgcommand.h"
#include "server/commands/commands/ircquitcommand.h"
#include "server/commands/commands/ircusercommand.h"

namespace ircserv
{

IRCCommandsFactory::IRCCommandsFactory()
{
    Initialize();
}

void IRCCommandsFactory::Initialize(void)
{
}

IRCCommandsFactory::~IRCCommandsFactory()
{
    Shutdown();
}

void IRCCommandsFactory::Shutdown(void)
{
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
