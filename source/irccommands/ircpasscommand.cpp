#include "main/precomp.h"

#include "irccommands/ircpasscommand.h"

#include "ircclient/ircclient.h"
#include "irccommands/irccommands.h"
#include "ircresponses/ircresponseshelper.h"
#include "ircresponses/ircresponses.h"
#include "ircserver/ircsocket.h"
#include "managers/ircclientsmanager.h"

namespace ircserv
{

IRCPassCommand::IRCPassCommand() : IRCCommand(Enum_IRCCommands_Pass)
{
    Initialize();
}

void IRCPassCommand::Initialize(void)
{
}

IRCPassCommand::~IRCPassCommand()
{
    Shutdown();
}

void IRCPassCommand::Shutdown(void)
{
}

bool IRCPassCommand::ProcessCommand(IRCSocket *socket)
{
    if (ValidateArgs(socket))
    {
        IRCClient *client = GetIRCClientsManager().FindOrCreateClient(socket);

        if (client->GetIsRegistered())
        {
            IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_ALREADYREGISTRED);
        }
        else
        {
            client->SetPassword(GetPassword());
            return true;
        }
    }
    return false;
}

bool IRCPassCommand::ValidateArgs(IRCSocket *socket)
{
    if (GetArgs().empty())
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NEEDMOREPARAMS, EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
        return false;
    }
    SetPassword(GetArgs()[0]);
    return true;
}

}
