#include "main/precomp.h"

#include "irccommands/irclistcommand.h"

#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
#include "ircresponses/ircresponseshelper.h"
#include "parsing/ircparsinghelper.h"

namespace ircserv
{

IRCListCommand::IRCListCommand() : IRCCommand(Enum_IRCCommands_List)
{
    Initialize();
}

void IRCListCommand::Initialize(void)
{
}

IRCListCommand::~IRCListCommand()
{
    Shutdown();
}

void IRCListCommand::Shutdown(void)
{
}

bool IRCListCommand::ProcessCommand(IRCSocket *socket)
{
    if (!IRCCommandsHelper::IsRegistered(socket))
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOTREGISTERED);
        return false;
    }

    if (ValidateArgs(socket))
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_RPL_LISTSTART);

        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_RPL_LISTEND);
        return true;
    }
    return false;
}

bool IRCListCommand::ValidateArgs(IRCSocket *socket)
{
    if (!GetArgs().empty())
    {
        SetChannels(IRCParsingHelper::Split(GetArgs()[0], ","));
    }
    return true;
}
}
