#include "main/precomp.h"

#include "server/commands/commands/ircpartcommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/parsing/ircsymbolsdefinition.h"
#include "server/commands/responses/ircresponseerr_needmoreparams.h"
#include "server/commands/responses/ircresponsesfactory.h"

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

bool IRCPartCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCPartCommand::ValidateArgs(/*serverclass */)
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
    }
    return true;
}

bool IRCPartCommand::SetChannels(const std::string& channels)
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

bool IRCPartCommand::SetChannel(const std::string& channel)
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

}
