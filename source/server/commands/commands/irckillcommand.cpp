#include "main/precomp.h"

#include "server/commands/commands/irckillcommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/parsing/ircparsinghelper.h"
#include "server/commands/responses/ircresponseerr_needmoreparams.h"
#include "server/commands/responses/ircresponsesfactory.h"

namespace ircserv
{

IRCKillCommand::IRCKillCommand() : IRCCommand(Enum_IRCCommands_Kill)
{
    Initialize();
}

void IRCKillCommand::Initialize(void)
{
}

IRCKillCommand::~IRCKillCommand()
{
    Shutdown();
}

void IRCKillCommand::Shutdown(void)
{
}

bool IRCKillCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCKillCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.size() < 2)
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
        if (!IRCParsingHelper::IsNick(m_Args[0]))
        {
            return false;
        }
        SetNickname(m_Args[0]);
        SetComment(m_Args[1]);
    }
    return true;
}
}
