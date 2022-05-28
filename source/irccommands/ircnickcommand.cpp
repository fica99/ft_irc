#include "main/precomp.h"

#include "irccommands/ircnickcommand.h"

#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
#include "ircresponses/ircresponses.h"
#include "ircserver/ircserver.h"
#include "ircserver/ircsocket.h"
#include "managers/ircclientsmanager.h"
#include "parsing/ircparsinghelper.h"

namespace ircserv
{

IRCNickCommand::IRCNickCommand() : IRCCommand(Enum_IRCCommands_Nick)
{
    Initialize();
}

void IRCNickCommand::Initialize(void)
{
}

IRCNickCommand::~IRCNickCommand()
{
    Shutdown();
}

void IRCNickCommand::Shutdown(void)
{
}

bool IRCNickCommand::ProcessCommand(IRCSocket* socket)
{
    if (ValidateArgs(socket))
    {
        Enum_IRCResponses enumResponse = GetIRCClientsManager().Nick(socket, GetNickname());

        if (enumResponse == Enum_IRCResponses_ERR_NICKNAMEINUSE)
        {
            IRCCommandsHelper::SendERR_NICKNAMEINUSE(socket, GetNickname());
            return false;
        }
        else if (enumResponse == Enum_IRCResponses_RPL_MOTD)
        {
            IRCCommandsHelper::SendMOTD(socket, GetIRCServer().GetServerName(), "./conf/IRC.motd");
        }
        return true;
    }
    return false;
}

bool IRCNickCommand::ValidateArgs(IRCSocket* socket)
{
    if (GetArgs().empty())
    {
        IRCCommandsHelper::SendResponseWithoutParams(socket, Enum_IRCResponses_ERR_NONICKNAMEGIVEN);
        return false;
    }
    else
    {
        if (!IRCParsingHelper::IsNick(GetArgs()[0]))
        {
            IRCCommandsHelper::SendERR_ERRONEUSNICKNAME(socket, GetArgs()[0]);
            return false;
        }
        SetNickname(GetArgs()[0]);
    }
    return true;
}


}
