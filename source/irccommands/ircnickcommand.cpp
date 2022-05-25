#include "main/precomp.h"

#include "irccommands/ircnickcommand.h"
#include "irccommands/irccommands.h"

#include "parsing/ircparsinghelper.h"
#include "ircresponses/ircresponseerr_erroneusnickname.h"
#include "ircresponses/ircresponseerr_nonicknamegiven.h"
#include "ircresponses/ircresponseerr_nickcollision.h"
#include "ircresponses/ircresponseerr_nicknameinuse.h"
#include "ircresponses/ircresponsesfactory.h"

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

bool IRCNickCommand::ProcessCommand(IRCSocket* socket)
{
    if (ValidateArgs(socket))
    {
        // IRCResponse* response = GetIRCResponsesFactory().CreateResponse(serv->setNickname(GetNickname()));

        // if (response)
        // {
        //     IRCResponseERR_NICKCOLLISION *responseNickCollision = dynamic_cast<IRCResponseERR_NICKCOLLISION*>(response);
        //     IRCResponseERR_NICKNAMEINUSE *responseNicknameInUse = dynamic_cast<IRCResponseERR_NICKNAMEINUSE*>(response);

        //     if (responseNickCollision != NULL)
        //     {
        //         responseNickCollision->SetNick(m_Args[0]);
        //         serv->sendResponse(responseNickCollision->GetResponse());
        //     }
        //     else if (responseNicknameInUse != NULL)
        //     {
        //         responseNicknameInUse->SetNick(m_Args[0]);
        //         serv->sendResponse(responseNicknameInUse->GetResponse());
        //     }

        //     GetIRCResponsesFactory().DestroyResponse(response);
        //     return false;
        // }
        return true;
    }
    return false;
}

bool IRCNickCommand::ValidateArgs(IRCSocket* socket)
{
    // if (m_Args.empty())
    // {
    //     IRCResponseERR_NONICKNAMEGIVEN* response = dynamic_cast<IRCResponseERR_NONICKNAMEGIVEN*>(
    //         GetIRCResponsesFactory().CreateResponse(Enum_IRCResponses_ERR_NONICKNAMEGIVEN)
    //     );
    //     if (response != NULL)
    //     {
    //         serv->sendResponse(response->GetResponse());
    //     }
    //     GetIRCResponsesFactory().DestroyResponse(response);
    //     return false;
    // }
    // else
    // {
    //     if (!IRCParsingHelper::IsNick(m_Args[0]))
    //     {
    //         IRCResponseERR_ERRONEUSNICKNAME* response = dynamic_cast<IRCResponseERR_ERRONEUSNICKNAME*>(
    //             GetIRCResponsesFactory().CreateResponse(Enum_IRCResponses_ERR_ERRONEUSNICKNAME)
    //         );
    //         if (response != NULL)
    //         {
    //             response->SetNick(m_Args[0]);
    //             serv->sendResponse(response->GetResponse());
    //         }
    //         GetIRCResponsesFactory().DestroyResponse(response);
    //         return false;
    //     }
    //     SetNickname(m_Args[0]);
    // }
    return true;
}


}
