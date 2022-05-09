#include "main/precomp.h"

#include "server/commands/commands/ircopercommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/parsing/ircparsinghelper.h"
#include "server/commands/responses/ircresponseerr_needmoreparams.h"
#include "server/commands/responses/ircresponserpl_youreoper.h"
#include "server/commands/responses/ircresponsesfactory.h"

namespace ircserv
{

IRCOperCommand::IRCOperCommand() : IRCCommand(Enum_IRCCommands_Oper)
{
    Initialize();
}

void IRCOperCommand::Initialize(void)
{
}

IRCOperCommand::~IRCOperCommand()
{
    Shutdown();
}

void IRCOperCommand::Shutdown(void)
{
}

bool IRCOperCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        IRCResponseRPL_YOUREOPER* response = dynamic_cast<IRCResponseRPL_YOUREOPER*>(
            GetIRCResponsesFactory().CreateResponse(Enum_IRCResponses_RPL_YOUREOPER)
        );
        // send response
        GetIRCResponsesFactory().DestroyResponse(response);
        return true;
    }
    return false;
}

bool IRCOperCommand::ValidateArgs(/*serverclass */)
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
        if (!IRCParsingHelper::IsUser(m_Args[0]))
        {
            return false;
        }
        SetUser(m_Args[1]);
        SetPassword(m_Args[1]);
    }
    return true;
}

}
