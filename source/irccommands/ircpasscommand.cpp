#include "main/precomp.h"

#include "irccommands/ircpasscommand.h"
#include "irccommands/irccommands.h"

#include "ircresponses/ircresponseerr_needmoreparams.h"
#include "ircresponses/ircresponseerr_alreadyregistered.h"
#include "ircresponses/ircresponsesfactory.h"
#include "ircserver/ircsocket.h"
#include "managers/ircclientsmanager.h"

namespace ircserv
{

IRCPassCommand::IRCPassCommand() : IRCCommand(Enum_IRCCommands_Pass)
{
    Initialize();
}

void IRCPassCommand::Initialize(void)
{
}

IRCPassCommand::~IRCPassCommand()
{
    Shutdown();
}

void IRCPassCommand::Shutdown(void)
{
}

bool IRCPassCommand::ProcessCommand(IRCSocket *socket)
{
    if (ValidateArgs(socket))
    {
        if (GetIRCClientsManager().Pass(socket, GetPassword()) == false)
        {
            IRCResponse* response = IRCResponsesFactory::CreateResponse(Enum_IRCResponses_ERR_ALREADYREGISTRED);
            if (response != NULL && socket != NULL)
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

bool IRCPassCommand::ValidateArgs(IRCSocket *socket)
{
    if (GetArgs().empty())
    {
        IRCResponseERR_NEEDMOREPARAMS* response = dynamic_cast<IRCResponseERR_NEEDMOREPARAMS*>(
            IRCResponsesFactory::CreateResponse(Enum_IRCResponses_ERR_NEEDMOREPARAMS)
        );
        if (response != NULL)
        {
            response->SetCommand(EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
            if (socket != NULL)
            {
                socket->Send(response->GetResponse());
                IRC_LOGD("Send %s response for %s command! Response: %s", EnumString<Enum_IRCResponses>::From(response->GetResponseEnum()).c_str(), EnumString<Enum_IRCCommands>::From(GetCommandEnum()).c_str(), response->GetResponse().c_str());
            }
        }
        IRCResponsesFactory::DestroyResponse(response);
        return false;
    }
    SetPassword(GetArgs()[0]);
    return true;
}

}
