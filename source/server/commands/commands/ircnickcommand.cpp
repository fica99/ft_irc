#include "main/precomp.h"

#include "server/commands/commands/ircnickcommand.h"

#include "server/ircserver.h"
#include "server/commands/commands/irccommands.h"
#include "server/commands/parsing/ircparsinghelper.h"
#include "server/commands/responses/ircresponseerr_erroneusnickname.h"
#include "server/commands/responses/ircresponseerr_nonicknamegiven.h"
#include "server/commands/responses/ircresponseerr_nickcollision.h"
#include "server/commands/responses/ircresponseerr_nicknameinuse.h"
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

bool IRCNickCommand::ProcessCommand(IRCServer *serv)
{
    if (ValidateArgs(serv))
    {
        IRCResponse* response = GetIRCResponsesFactory().CreateResponse(serv->setNickname(m_Args[0]));

        if (response)
        {
            IRCResponseERR_NICKCOLLISION *responseNickCollision = dynamic_cast<IRCResponseERR_NICKCOLLISION*>(response);
            IRCResponseERR_NICKNAMEINUSE *responseNicknameInUse = dynamic_cast<IRCResponseERR_NICKNAMEINUSE*>(response);

            if (responseNickCollision != NULL)
            {
                responseNickCollision->SetNick(m_Args[0]);
                send(serv->m_Curr->fd, responseNickCollision->GetResponse().c_str(), responseNickCollision->GetResponse().size(), 0);
            }
            else if (responseNicknameInUse != NULL)
            {
                responseNicknameInUse->SetNick(m_Args[0]);
                int i = send(serv->m_Curr->fd, responseNicknameInUse->GetResponse().c_str(), responseNicknameInUse->GetResponse().size(), 0);
                perror("send");
            }

            GetIRCResponsesFactory().DestroyResponse(response);
            return false;
        }
        return true;
    }
    return false;
}

bool IRCNickCommand::ValidateArgs(IRCServer *serv)
{
    if (m_Args.empty())
    {
        IRCResponseERR_NONICKNAMEGIVEN* response = dynamic_cast<IRCResponseERR_NONICKNAMEGIVEN*>(
            GetIRCResponsesFactory().CreateResponse(Enum_IRCResponses_ERR_NONICKNAMEGIVEN)
        );
        send(serv->m_Curr->fd, response->GetResponse().c_str(), response->GetResponse().size(), 0);
        GetIRCResponsesFactory().DestroyResponse(response);
        return false;
    }
    else
    {
        if (!IRCParsingHelper::IsNick(m_Args[0]))
        {
            IRCResponseERR_ERRONEUSNICKNAME* response = dynamic_cast<IRCResponseERR_ERRONEUSNICKNAME*>(
                GetIRCResponsesFactory().CreateResponse(Enum_IRCResponses_ERR_ERRONEUSNICKNAME)
            );
            if (response != NULL)
            {
                response->SetNick(m_Args[0]);
                send(serv->m_Curr->fd, response->GetResponse().c_str(), response->GetResponse().size(), 0);
            }
            GetIRCResponsesFactory().DestroyResponse(response);
            return false;
        }
        SetNickname(m_Args[0]);
    }
    return true;
}


}
