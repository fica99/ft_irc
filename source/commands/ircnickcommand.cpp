#include "main/precomp.h"

#include "commands/ircnickcommand.h"

#include "commands/irccommands.h"
#include "responses/ircresponseerr_nonicknamegiven.h"
#include "responses/ircresponsesfactory.h"

namespace ircserv
{

IRCNickCommand::IRCNickCommand() : IRCCommand(Enum_IRCCommands_Nick)
{
    Initialize();
}

void IRCNickCommand::Initialize(void)
{
}

IRCNickCommand::~IRCNickCommand()
{
    Shutdown();
}

void IRCNickCommand::Shutdown(void)
{
}

bool IRCNickCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCNickCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.empty())
    {
        IRCResponseERR_NONICKNAMEGIVEN* response = dynamic_cast<IRCResponseERR_NONICKNAMEGIVEN*>(
            GetIRCResponsesFactory().CreateResponse(Enum_IRCResponses_ERR_NONICKNAMEGIVEN)
        );
        GetIRCResponsesFactory().DestroyResponse(response);
        return false;
    }
    return true;
}
}
