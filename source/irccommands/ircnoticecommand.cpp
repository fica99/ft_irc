#include "main/precomp.h"

#include "irccommands/ircnoticecommand.h"

#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
#include "parsing/ircparsinghelper.h"
#include "ircresponses/ircresponseshelper.h"
#include "managers/ircclientsmanager.h"

namespace ircserv
{

IRCNoticeCommand::IRCNoticeCommand() : IRCCommand(Enum_IRCCommands_Notice)
{
    Initialize();
}

void IRCNoticeCommand::Initialize(void)
{
}

IRCNoticeCommand::~IRCNoticeCommand()
{
    Shutdown();
}

void IRCNoticeCommand::Shutdown(void)
{
}

bool IRCNoticeCommand::ValidateArgs(IRCSocket *socket)
{
    (void)(socket);
    if (GetArgs().empty())
    {
        return false;
    }
    else if (GetArgs().size() < 2 || GetArgs()[1].empty())
    {
        return false;
    }
    SetNickname(GetArgs()[0]);
    SetText(GetArgs()[1]);
    return true;
}
bool IRCNoticeCommand::ProcessCommand(IRCSocket *socket)
{
    if (!IRCCommandsHelper::IsRegistered(socket))
    {
        return false;
    }

    if (ValidateArgs(socket))
    {
        IRCClient *client = GetIRCClientsManager().FindClient(socket);
        if (client == NULL)
        {
            return false;
        }
        std::string message = ":" + client->GetNickname() + "!" + client->GetUsername() + "@" + client->GetHostname() + " " + EnumString<Enum_IRCCommands>::From(GetCommandEnum()) + " " + GetNickname() + " :" + GetText() + "\n";

        IRCClient *receiverClient = GetIRCClientsManager().FindClientByNickname(GetNickname());
        if (receiverClient == NULL)
        {
            return false;
        }
        IRCSocket *receiverSocket = GetIRCClientsManager().FindSocketByClient(receiverClient);
        if (receiverSocket)
        {
            IRCResponsesHelper::Send(receiverSocket, message);
        }
        return true;
    }
    return false;
}

}
