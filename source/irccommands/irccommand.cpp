#include "main/precomp.h"

#include "irccommands/irccommand.h"

namespace ircserv
{

IRCCommand::IRCCommand()
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
