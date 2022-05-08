#include "main/precomp.h"

#include "server/commands/commands/ircnamescommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/parsing/ircsymbolsdefinition.h"
#include "server/commands/responses/ircresponsesfactory.h"

namespace ircserv
{

IRCNamesCommand::IRCNamesCommand() : IRCCommand(Enum_IRCCommands_Names)
{
    Initialize();
}

void IRCNamesCommand::Initialize(void)
{
}

IRCNamesCommand::~IRCNamesCommand()
{
    Shutdown();
}

void IRCNamesCommand::Shutdown(void)
{
}

bool IRCNamesCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCNamesCommand::ValidateArgs(/*serverclass */)
{
    if (!m_Args.empty())
    {
        if (!SetChannels(m_Args[0]))
        {
            return false;
        }
    }
    return true;
}

bool IRCNamesCommand::SetChannels(const std::string& channels)
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

bool IRCNamesCommand::SetChannel(const std::string& channel)
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
