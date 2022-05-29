#include "main/precomp.h"

#include "irccommands/ircopercommand.h"

#include "ircclient/ircclient.h"
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
        IRCCommandsHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOTREGISTERED);
        return false;
    }

    if (ValidateArgs(socket))
    {
        Enum_IRCResponses responseEnum = Enum_IRCResponses_ERR_NOOPERHOST;
        if (!GetIRCClientsManager().IsOperMapEmpty())
        {
            if (GetIRCClientsManager().IsOper(GetUser(), GetPassword()))
            {
                IRCClient *client = GetIRCClientsManager().FindClient(socket);
                if (client)
                {
                    client->SetModes(IRCOPERATOR);
                }
                responseEnum = Enum_IRCResponses_RPL_YOUREOPER;
            }
            else
            {
                responseEnum = Enum_IRCResponses_ERR_PASSWDMISMATCH;
            }
        }
        IRCCommandsHelper::SendResponseWithParams(socket, responseEnum);
        return responseEnum == Enum_IRCResponses_RPL_YOUREOPER;
    }
    return false;
}

bool IRCOperCommand::ValidateArgs(IRCSocket *socket)
{
    if (GetArgs().size() < 2)
    {
        IRCCommandsHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NEEDMOREPARAMS, EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
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
