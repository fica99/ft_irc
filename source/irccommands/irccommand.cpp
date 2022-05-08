#include "main/precomp.h"

#include "irccommands/irccommand.h"

namespace ircserv
{

IRCCommand::IRCCommand() : m_CommandType(Enum_IRCCommands_Unknown)
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

bool IRCCommand::ProcessCommand(Server *s, std::pair<const int, Client> &client)
{
    return true;
}

}
