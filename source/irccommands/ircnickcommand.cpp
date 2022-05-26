#include "main/precomp.h"

#include "irccommands/ircnickcommand.h"

#include "irccommands/irccommands.h"
#include "ircresponses/ircresponseerr_erroneusnickname.h"
#include "ircresponses/ircresponseerr_nonicknamegiven.h"
#include "ircresponses/ircresponseerr_nickcollision.h"
#include "ircresponses/ircresponseerr_nicknameinuse.h"
#include "ircresponses/ircresponsesfactory.h"
#include "ircserver/ircsocket.h"
#include "managers/ircclientsmanager.h"
#include "parsing/ircparsinghelper.h"

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
        IRCResponse* response = IRCResponsesFactory::CreateResponse(GetIRCClientsManager().Nick(socket, GetNickname()));

        if (response)
        {
            IRCResponseERR_NICKCOLLISION *responseNickCollision = dynamic_cast<IRCResponseERR_NICKCOLLISION*>(response);
            IRCResponseERR_NICKNAMEINUSE *responseNicknameInUse = dynamic_cast<IRCResponseERR_NICKNAMEINUSE*>(response);

            if (responseNickCollision != NULL)
            {
                responseNickCollision->SetNick(GetArgs()[0]);
            }
            else if (responseNicknameInUse != NULL)
            {
                responseNicknameInUse->SetNick(GetArgs()[0]);
            }

            if (socket != NULL)
            {
                socket->Send(response->GetResponse());
                IRC_LOGD("Send %s response for %s command! Response: %s", EnumString<Enum_IRCResponses>::From(response->GetResponseEnum()).c_str(), EnumString<Enum_IRCCommands>::From(GetCommandEnum()).c_str(), response->GetResponse().c_str());
            }

            IRCResponsesFactory::DestroyResponse(response);
            return false;
        }
        return true;
    }
    return false;
}

bool IRCNickCommand::ValidateArgs(IRCSocket* socket)
{
    if (GetArgs().empty())
    {
        IRCResponse* response = IRCResponsesFactory::CreateResponse(Enum_IRCResponses_ERR_NONICKNAMEGIVEN);
        if (response != NULL && socket != NULL)
        {
            socket->Send(response->GetResponse());
            IRC_LOGD("Send %s response for %s command! Response: %s", EnumString<Enum_IRCResponses>::From(response->GetResponseEnum()).c_str(), EnumString<Enum_IRCCommands>::From(GetCommandEnum()).c_str(), response->GetResponse().c_str());
        }
        IRCResponsesFactory::DestroyResponse(response);
        return false;
    }
    else
    {
        if (!IRCParsingHelper::IsNick(GetArgs()[0]))
        {
            IRCResponseERR_ERRONEUSNICKNAME* response = dynamic_cast<IRCResponseERR_ERRONEUSNICKNAME*>(
                IRCResponsesFactory::CreateResponse(Enum_IRCResponses_ERR_ERRONEUSNICKNAME)
            );
            if (response != NULL && socket != NULL)
            {
                response->SetNick(GetArgs()[0]);
                socket->Send(response->GetResponse());
                IRC_LOGD("Send %s response for %s command! Response: %s", EnumString<Enum_IRCResponses>::From(response->GetResponseEnum()).c_str(), EnumString<Enum_IRCCommands>::From(GetCommandEnum()).c_str(), response->GetResponse().c_str());
            }
            IRCResponsesFactory::DestroyResponse(response);
            return false;
        }
        SetNickname(GetArgs()[0]);
    }
    return true;
}


}
