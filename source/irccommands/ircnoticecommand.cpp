#include "main/precomp.h"

#include "irccommands/ircnoticecommand.h"
#include "irccommands/irccommands.h"

#include "parsing/ircparsinghelper.h"
#include "ircresponses/ircresponsesfactory.h"
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
//
bool IRCNoticeCommand::ValidateArgs(IRCSocket *socket)
{
	if (GetArgs().empty())
	{
		IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NORECIPIENT, EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
		return false;
	}
	else if (GetArgs().size() < 2)
	{
		IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOTEXTTOSEND, EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
		return false;
	}
	return true;
}
bool IRCNoticeCommand::ProcessCommand(IRCSocket *socket)
{
	if (ValidateArgs(socket))
	{
		IRCClient *cl = GetIRCClientsManager().FindClientByNickname(GetArgs()[0]);
		if (cl)
		{
			GetIRCClientsManager().FindSocketByClient(cl)->Send(GetArgs()[1]);
		}
		else
		{
			IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NORECIPIENT, EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
		}
		return true;
	}
	return false;
}

}
