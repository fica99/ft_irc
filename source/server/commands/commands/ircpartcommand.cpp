#include "main/precomp.h"

#include "server/commands/commands/ircpartcommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/parsing/ircparsinghelper.h"
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

bool IRCPartCommand::ProcessCommand(IRCServer *serv)
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
        if (!IRCParsingHelper::IsChannels(m_Args[0]))
        {
            return false;
        }
        SetChannels(IRCParsingHelper::Split(m_Args[0], ","));
    }
    return true;
}

}
