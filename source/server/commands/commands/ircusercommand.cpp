#include "main/precomp.h"

#include "server/commands/commands/ircusercommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/parsing/ircparsinghelper.h"
#include "server/commands/responses/ircresponseerr_needmoreparams.h"
#include "server/commands/responses/ircresponsesfactory.h"

namespace ircserv
{

IRCUserCommand::IRCUserCommand() : IRCCommand(Enum_IRCCommands_User)
{
    Initialize();
}

void IRCUserCommand::Initialize(void)
{
}

IRCUserCommand::~IRCUserCommand()
{
    Shutdown();
}

void IRCUserCommand::Shutdown(void)
{
}

bool IRCUserCommand::ProcessCommand(Server *serv)
{
    if (ValidateArgs(/*serverclass */))
    {
        serv->setPrefix(m_Args[0]);
        return true;
    }
    return false;
}

bool IRCUserCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.size() < 4)
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
        if (!IRCParsingHelper::IsUser(m_Args[0]) || !IRCParsingHelper::IsRealname(m_Args[3]))
        {
            return false;
        }
        SetUsername(m_Args[0]);
        SetRealname(m_Args[3]);
    }
    return true;
}

}
