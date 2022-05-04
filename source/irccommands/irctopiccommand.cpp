#include "main/precomp.h"

#include "irccommands/irctopiccommand.h"

#include "irccommands/irccommands.h"
#include "ircresponses/ircresponsesfactory.h"

namespace ircserv
{

IRCTopicCommand::IRCTopicCommand() : IRCCommand(Enum_IRCCommands_Topic)
{
    Initialize();
}

void IRCTopicCommand::Initialize(void)
{
}

IRCTopicCommand::~IRCTopicCommand()
{
    Shutdown();
}

void IRCTopicCommand::Shutdown(void)
{
}

bool IRCTopicCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCTopicCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.empty())
    {

        return false;
    }
    return true;
}

}
