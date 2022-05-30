#include "main/precomp.h"

#include "irccommands/ircpartcommand.h"

#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
#include "ircresponses/ircresponses.h"
#include "managers/ircclientsmanager.h"
#include "managers/ircchannelsmanager.h"
#include "parsing/ircparsinghelper.h"


namespace ircserv
{

IRCPartCommand::IRCPartCommand() : IRCCommand(Enum_IRCCommands_Part)
{
    Initialize();
}

void IRCPartCommand::Initialize(void)
{
}

IRCPartCommand::~IRCPartCommand()
{
    Shutdown();
}

void IRCPartCommand::Shutdown(void)
{
}

bool IRCPartCommand::ProcessCommand(IRCSocket *socket)
{
    // if (!GetIRCClientsManager().IsRegistered(socket))
    // {
    //     IRCResponsesHelper::SendResponseWithoutParams(socket, Enum_IRCResponses_ERR_NOTREGISTERED);
    //     return false;
    // }

    // if (ValidateArgs(socket))
    // {
    //     for (std::vector<std::string>::iterator it = m_Channels.begin(); it != m_Channels.end(); )
    //     {
    //         Enum_IRCResponses responseEnum = GetIRCChannelsManager().Part(socket, *it);
    //         IRCResponsesHelper::SendResponseWithServerName(socket, responseEnum, *it);
    //     }
    //     return true;
    // }
    return false;
}

bool IRCPartCommand::ValidateArgs(IRCSocket *socket)
{
    // std::vector<std::string> channels;
    // if (GetArgs().empty())
    // {
    //     IRCResponsesHelper::SendResponseWithoutParams(socket, Enum_IRCResponses_ERR_NEEDMOREPARAMS);
    //     return false;
    // }
    // else
    // {
    //     channels = IRCParsingHelper::Split(GetArgs()[0], ",");
    //     for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); )
    //     {
    //         if (!IRCParsingHelper::IsChannel(*it))
    //         {
    //             IRCResponsesHelper::SendResponseWithServerName(socket, Enum_IRCResponses_ERR_NOSUCHCHANNEL, *it);
    //             it = channels.erase(it);
    //         }
    //         else
    //         {
    //             ++it;
    //         }
    //     }
    // }
    return true;
}

}
