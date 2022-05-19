#include "main/precomp.h"

#include "server/commands/commands/ircusercommand.h"

#include "server/ircserver.h"
#include "server/commands/commands/irccommands.h"
#include "server/commands/parsing/ircparsinghelper.h"
#include "server/commands/responses/ircresponseerr_alreadyregistered.h"
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

bool IRCUserCommand::ProcessCommand(IRCServer *serv)
{
    if (ValidateArgs(serv))
    {
        IRCResponse* response = GetIRCResponsesFactory().CreateResponse(serv->userCommand(m_Args[0]));

        if (response)
        {
            IRCResponseERR_ALREADYREGISTERED *responseAlreadyRegistered = dynamic_cast<IRCResponseERR_ALREADYREGISTERED*>(response);
            
            if (responseAlreadyRegistered != NULL)
            {
                serv->sendResponse(responseAlreadyRegistered->GetResponse());
            }

            GetIRCResponsesFactory().DestroyResponse(response);
            return false;
        }
        return true;
    }
    return false;
}

bool IRCUserCommand::ValidateArgs(IRCServer *serv)
{
    IRC_LOGD("%s", "User command");
    if (m_Args.size() < 4)
    {
        IRCResponseERR_NEEDMOREPARAMS* response = dynamic_cast<IRCResponseERR_NEEDMOREPARAMS*>(
            GetIRCResponsesFactory().CreateResponse(Enum_IRCResponses_ERR_NEEDMOREPARAMS)
        );
        if (response != NULL)
        {
            response->SetCommand(EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
            serv->sendResponse(response->GetResponse());
        }
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
