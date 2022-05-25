#include "main/precomp.h"

#include "irccommands/ircusercommand.h"
#include "irccommands/irccommands.h"

#include "parsing/ircparsinghelper.h"
#include "ircresponses/ircresponseerr_alreadyregistered.h"
#include "ircresponses/ircresponseerr_needmoreparams.h"
#include "ircresponses/ircresponsesfactory.h"

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

bool IRCUserCommand::ProcessCommand(IRCSocket *socket)
{
    // if (ValidateArgs(serv))
    // {
    //     IRCResponse* response = GetIRCResponsesFactory().CreateResponse(serv->userCommand(m_Args[0]));

    //     if (response)
    //     {
    //         IRCResponseERR_ALREADYREGISTERED *responseAlreadyRegistered = dynamic_cast<IRCResponseERR_ALREADYREGISTERED*>(response);
            
    //         if (responseAlreadyRegistered != NULL)
    //         {
    //             serv->sendResponse(responseAlreadyRegistered->GetResponse());
    //         }

    //         GetIRCResponsesFactory().DestroyResponse(response);
    //         return false;
    //     }
    //     return true;
    // }
    return false;
}

bool IRCUserCommand::ValidateArgs(IRCSocket *socket)
{
    IRC_LOGD("%s", "User command");
    // if (m_Args.size() < 4)
    // {
    //     IRCResponseERR_NEEDMOREPARAMS* response = dynamic_cast<IRCResponseERR_NEEDMOREPARAMS*>(
    //         GetIRCResponsesFactory().CreateResponse(Enum_IRCResponses_ERR_NEEDMOREPARAMS)
    //     );
    //     if (response != NULL)
    //     {
    //         response->SetCommand(EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
    //         serv->sendResponse(response->GetResponse());
    //     }
    //     GetIRCResponsesFactory().DestroyResponse(response);
    //     return false;
    // }
    // else
    // {
    //     if (!IRCParsingHelper::IsUser(m_Args[0]) || !IRCParsingHelper::IsRealname(m_Args[3]))
    //     {
    //         return false;
    //     }
    //     SetUsername(m_Args[0]);
    //     SetRealname(m_Args[3]);
    // }
    return true;
}

}
