#include "main/precomp.h"

#include "irccommands/ircquitcommand.h"

#include "ircclient/ircclient.h"
#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
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
    if (!GetArgs().empty())
    {
        SetQuitMessage(GetArgs()[0]);
    }
    IRCClient *client = GetIRCClientsManager().FindClient(socket);
    if (client)
    {
        std::unordered_set<IRCChannel*> channelsJoined = client->GetJoinedChannels();
        for (std::unordered_set<IRCChannel*>::iterator it = channelsJoined.begin(); it != channelsJoined.end(); ++it)
        {
            IRCCommandsHelper::EraseClientFromChannel(client, *it);
        }
    }
    GetIRCClientsManager().EraseClient(socket);
    GetIRCServer().CloseConnection(socket);
    return true;
}

}
