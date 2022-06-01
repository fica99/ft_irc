#include "main/precomp.h"

#include "irccommands/irccommandsfactory.h"

#include "utils/memory.h"
#include "irccommands/irccommand.h"
#include "irccommands/ircjoincommand.h"
#include "irccommands/irckickcommand.h"
#include "irccommands/irclistcommand.h"
#include "irccommands/ircnamescommand.h"
#include "irccommands/ircnickcommand.h"
#include "irccommands/ircnoticecommand.h"
#include "irccommands/ircopercommand.h"
#include "irccommands/ircpartcommand.h"
#include "irccommands/ircpasscommand.h"
#include "irccommands/ircprivmsgcommand.h"
#include "irccommands/ircquitcommand.h"
#include "irccommands/irctopiccommand.h"
#include "irccommands/ircusercommand.h"
#include "irccommands/ircinvitecommand.h"

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
        case Enum_IRCCommands_Topic:
            command = New(IRCTopicCommand)();
            break;
        case Enum_IRCCommands_Invite:
            command = New(IRCInviteCommand)();
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
