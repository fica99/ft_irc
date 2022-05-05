#include "main/precomp.h"

#include "commands/irccommand.h"

namespace ircserv
{

IRCCommand::IRCCommand(Enum_IRCCommands commandEnum) : m_CommandEnum(commandEnum)
{
    Initialize();
}

void IRCCommand::Initialize(void)
{
}

IRCCommand::~IRCCommand()
{
    Shutdown();
}

void IRCCommand::Shutdown(void)
{
}

}
