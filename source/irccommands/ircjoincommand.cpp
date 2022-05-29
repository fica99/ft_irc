#include "main/precomp.h"

#include "irccommands/ircjoincommand.h"

#include "ircchannel/ircchannel.h"
#include "ircclient/ircclient.h"
#include "irccommands/irccommands.h"
#include "irccommands/irccommandshelper.h"
#include "ircresponses/ircresponses.h"
#include "ircserver/ircserver.h"
#include "managers/ircchannelsmanager.h"
#include "managers/ircclientsmanager.h"
#include "parsing/ircparsinghelper.h"

namespace ircserv
{

IRCJoinCommand::IRCJoinCommand() : IRCCommand(Enum_IRCCommands_Join)
{
    Initialize();
}

void IRCJoinCommand::Initialize(void)
{
}

IRCJoinCommand::~IRCJoinCommand()
{
    Shutdown();
}

void IRCJoinCommand::Shutdown(void)
{
}

bool IRCJoinCommand::ProcessCommand(IRCSocket *socket)
{
    if (!GetIRCClientsManager().IsRegistered(socket))
    {
        IRCCommandsHelper::SendResponseWithoutParams(socket, Enum_IRCResponses_ERR_NOTREGISTERED);
        return false;
    }

    if (ValidateArgs(socket))
    {
        for (size_t i = 0; i < GetChannels().size(); ++i)
        {
            Enum_IRCResponses responseEnum = GetIRCChannelsManager().Join(socket, GetChannels()[i], i < GetKeys().size() ? GetKeys()[i] : "");
            if (responseEnum == Enum_IRCResponses_RPL_TOPIC)
            {
               IRCChannel *channel = GetIRCChannelsManager().FindChannel(GetChannels()[i]);
               IRCCommandsHelper::SendResponseWithTopic(socket, GetChannels()[i], channel ? channel->GetTopic() : "");
            }
            else
            {
                IRCCommandsHelper::SendResponseWithServerName(socket, responseEnum, GetChannels()[i]);
            }
        }
        return true;
    }
    return false;
}

bool IRCJoinCommand::ValidateArgs(IRCSocket *socket)
{
    std::vector<std::string> channels;
    std::vector<std::string> keys;

    if (GetArgs().empty())
    {
        IRCCommandsHelper::SendERR_NEEDMOREPARAMS(socket, GetCommandEnum());
        return false;
    }
    else
    {
        channels = IRCParsingHelper::Split(GetArgs()[0], ",");
        if (GetArgs().size() > 1)
        {
            keys = IRCParsingHelper::Split(GetArgs()[1], ",");
        }
        size_t i = 0;
        for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); )
        {
            if (!IRCParsingHelper::IsChannel(*it))
            {
                IRCCommandsHelper::SendResponseWithServerName(socket, Enum_IRCResponses_ERR_NOSUCHCHANNEL, *it);
                if (i < keys.size())
                {
                    keys.erase(keys.begin() + i);
                }
                it = channels.erase(it);
            }
            else
            {
                ++it;
                ++i;
            }
        }
        SetChannels(channels);
        SetKeys(keys);
    }
    return true;
}


}
