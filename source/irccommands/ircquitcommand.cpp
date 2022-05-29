#include "main/precomp.h"

#include "irccommands/ircquitcommand.h"

#include "irccommands/irccommands.h"
#include "ircserver/ircserver.h"
#include "ircserver/ircsocket.h"
#include "managers/ircclientsmanager.h"

namespace ircserv
{

IRCQuitCommand::IRCQuitCommand() : IRCCommand(Enum_IRCCommands_Quit)
{
    Initialize();
}

void IRCQuitCommand::Initialize(void)
{
}

IRCQuitCommand::~IRCQuitCommand()
{
    Shutdown();
}

void IRCQuitCommand::Shutdown(void)
{
}

bool IRCQuitCommand::ProcessCommand(IRCSocket *socket)
{
    // add quiting all channels
    GetIRCClientsManager().EraseClient(socket);
    GetIRCServer().CloseConnection(socket);
    return true;
}

}
