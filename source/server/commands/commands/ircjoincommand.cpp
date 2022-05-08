#include "main/precomp.h"

#include "server/commands/commands/ircjoincommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/parsing/ircsymbolsdefinition.h"
#include "server/commands/responses/ircresponseerr_needmoreparams.h"
#include "server/commands/responses/ircresponsesfactory.h"

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

bool IRCJoinCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCJoinCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.empty())
    {
        IRCResponseERR_NEEDMOREPARAMS* response = dynamic_cast<IRCResponseERR_NEEDMOREPARAMS*>(
            GetIRCResponsesFactory().CreateResponse(Enum_IRCResponses_ERR_NEEDMOREPARAMS)
        );
        if (response != NULL)
        {
            response->SetCommand(EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
        }
        // send response
        GetIRCResponsesFactory().DestroyResponse(response);
        return false;
    }
    else
    {
        if (!SetChannels(m_Args[0]))
        {
            return false;
        }
        if (m_Args.size() > 1)
        {
            SetKeys(Split(m_Args[1], ","));
        }
    }
    return true;
}

bool IRCJoinCommand::SetChannels(const std::string& channels)
{
    size_t pos = 0;
    size_t prevPos = 0;
    std::string channel;

    while ((pos = channels.find(",", prevPos)) != channels.npos)
    {
        channel = channels.substr(prevPos, pos);
        if (!SetChannel(channels))
        {
            m_Channels.clear();
            return false;
        }
        prevPos = pos + 1;
    }

    channel = channels.substr(prevPos, pos);
    if (!SetChannel(channel))
    {
        m_Channels.clear();
        return false;
    }

    return true;
}

bool IRCJoinCommand::SetChannel(const std::string& channel)
{
    size_t pos = 0;

    if (channel.empty())
    {
        return false;
    }
    if (channel[0] != '&' && channel[0] != '#')
    {
        return false;
    }
    pos = channel.find_first_of(IRCSymbolsDefinition::NON_CHSTRING_ASCII);
    if (pos != channel.npos)
    {
        return false;
    }
    m_Channels.push_back(channel);
    return true;
}

std::vector<std::string> IRCJoinCommand::Split(std::string line, const std::string& delim)
{
    std::vector<std::string> parts;
    size_t pos = 0;

    while ((pos = line.find(delim)) != line.npos)
    {
        parts.push_back(line.substr(0, pos));
        line.erase(0, pos + delim.size());
    }
    parts.push_back(line);
    return parts;
}


}
