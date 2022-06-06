#include "main/precomp.h"

#include "irccommands/ircprivmsgcommand.h"
#include "irccommands/irccommands.h"

#include "ircresponses/ircresponseerr_norecipient.h"
#include "ircresponses/ircresponseshelper.h"
#include "managers/ircclientsmanager.h"
#include "managers/ircchannelsmanager.h"
namespace ircserv
{

IRCPrivmsgCommand::IRCPrivmsgCommand() : IRCCommand(Enum_IRCCommands_Privmsg)
{
    Initialize();
}

void IRCPrivmsgCommand::Initialize(void)
{
}

IRCPrivmsgCommand::~IRCPrivmsgCommand()
{
    Shutdown();
}

void IRCPrivmsgCommand::Shutdown(void)
{
}

bool IRCPrivmsgCommand::ProcessCommand(IRCSocket *socket)
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
			IRCChannel *ch = GetIRCChannelsManager().FindChannel(GetArgs()[0]);
			if (!ch)
			{
				IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NORECIPIENT, EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
			}
			else
			{
				std::unordered_set<IRCClient *> s = ch->GetClients();
				std::unordered_set<IRCClient *>::iterator it;
				for (it = s.begin(); it != s.end(); it++) {
					GetIRCClientsManager().FindSocketByClient(*it)->Send(GetArgs()[1]);
				}
			}
		}
		return true;
	}
	return false;
}

bool IRCPrivmsgCommand::ValidateArgs(IRCSocket *socket)
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


}
