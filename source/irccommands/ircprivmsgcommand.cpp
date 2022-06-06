#include "main/precomp.h"

#include "irccommands/ircprivmsgcommand.h"

#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
#include "ircresponses/ircresponses.h"
#include "ircresponses/ircresponseshelper.h"
#include "managers/ircclientsmanager.h"
#include "managers/ircchannelsmanager.h"
#include "parsing/ircparsinghelper.h"

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
    if (!IRCCommandsHelper::IsRegistered(socket))
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOTREGISTERED);
        return false;
    }

    if (ValidateArgs(socket))
    {
        IRCClient *client = GetIRCClientsManager().FindClient(socket);
        if (client == NULL)
        {
            return false;
        }
        for (std::vector<std::string>::const_iterator it = GetReceivers().begin(); it != GetReceivers().end(); ++it)
        {
            std::string message = ":" + client->GetNickname() + "!" + client->GetUsername() + "@" + client->GetHostname() + " " + EnumString<Enum_IRCCommands>::From(GetCommandEnum()) + " " + *it + " :" + GetTextToBeSent() + "\n";
            if (IRCParsingHelper::IsChannel(*it))
            {
                IRCChannel *channel = GetIRCChannelsManager().FindChannel(*it);
                if (channel == NULL)
                {
                    IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOSUCHNICK, *it);
                    return false;
                }
                if (!IRCCommandsHelper::IsInContainer(channel->GetClients(), client))
                {
                    if (channel->GetModes() & NOMSGOUT && !IRCCommandsHelper::IsInContainer(channel->GetOpers(), client))
                    {
                        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_CANNOTSENDTOCHAN, *it);
                        return false;
                    }
                }

                IRCResponsesHelper::SendMessageToAllChannelNames(*it, message, client->GetNickname());
            }
            else
            {
                IRCClient *receiverClient = GetIRCClientsManager().FindClientByNickname(*it);
                if (receiverClient == NULL)
                {
                    IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOSUCHNICK, *it);
                    return false;
                }
                IRCSocket *receiverSocket = GetIRCClientsManager().FindSocketByClient(receiverClient);
                if (receiverSocket)
                {
                    IRCResponsesHelper::Send(receiverSocket, message);
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
    else if (GetArgs().size() < 2 || GetArgs()[1].empty())
    {
        IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NOTEXTTOSEND);
        return false;
    }
    else
    {
        std::vector<std::string> receivers;

        receivers = IRCParsingHelper::Split(GetArgs()[0], ",");
        if (receivers.empty())
        {
            IRCResponsesHelper::SendResponseWithParams(socket, Enum_IRCResponses_ERR_NORECIPIENT, EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
            return false;
        }
        SetReceivers(receivers);
        SetTextToBeSent(GetArgs()[1]);
    }
    return true;
}


}
