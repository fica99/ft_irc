#include "main/precomp.h"

#include "irccommands/ircopercommand.h"

#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
#include "ircresponses/ircresponses.h"
#include "ircserver/ircsocket.h"
#include "managers/ircclientsmanager.h"

namespace ircserv
{

IRCOperCommand::IRCOperCommand() : IRCCommand(Enum_IRCCommands_Oper)
{
    Initialize();
}

void IRCOperCommand::Initialize(void)
{
}

IRCOperCommand::~IRCOperCommand()
{
    Shutdown();
}

void IRCOperCommand::Shutdown(void)
{
}

bool IRCOperCommand::ProcessCommand(IRCSocket *socket)
{
    if (!GetIRCClientsManager().IsRegistered(socket))
    {
        IRCCommandsHelper::SendResponseWithoutParams(socket, Enum_IRCResponses_ERR_NOTREGISTERED);
        return false;
    }

    if (ValidateArgs(socket))
    {
        Enum_IRCResponses responseEnum = GetIRCClientsManager().Oper(socket, GetUser(), GetPassword());
        IRCCommandsHelper::SendResponseWithoutParams(socket, responseEnum);
        return responseEnum == Enum_IRCResponses_RPL_YOUREOPER;
    }
    return false;
}

bool IRCOperCommand::ValidateArgs(IRCSocket *socket)
{
    if (GetArgs().size() < 2)
    {
        IRCCommandsHelper::SendERR_NEEDMOREPARAMS(socket, GetCommandEnum());
        return false;
    }
    else
    {
        SetUser(GetArgs()[0]);
        SetPassword(GetArgs()[1]);
    }
    return true;
}

}
