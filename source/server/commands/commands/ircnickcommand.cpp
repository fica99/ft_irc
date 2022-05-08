#include "main/precomp.h"

#include "server/commands/commands/ircnickcommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/responses/ircresponseerr_nonicknamegiven.h"
#include "server/commands/responses/ircresponsesfactory.h"

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

bool IRCNickCommand::ProcessCommand(Server *serv)
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
