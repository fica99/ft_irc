#include "main/precomp.h"

#include "server/commands/commands/ircjoincommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/parsing/ircparsinghelper.h"
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

bool IRCJoinCommand::ProcessCommand(Server *serv)
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
        if (!IRCParsingHelper::IsChannels(m_Args[0]))
        {
            return false;
        }
        SetChannels(IRCParsingHelper::Split(m_Args[0], ","));
        if (m_Args.size() > 1)
        {
            SetKeys(IRCParsingHelper::Split(m_Args[1], ","));
        }
    }
    return true;
}


}
