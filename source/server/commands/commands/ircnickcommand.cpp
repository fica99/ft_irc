#include "main/precomp.h"

#include "server/commands/commands/ircnickcommand.h"

#include "server/ircserver.h"
#include "server/commands/commands/irccommands.h"
#include "server/commands/parsing/ircparsinghelper.h"
#include "server/commands/responses/ircresponseerr_erroneusnickname.h"
#include "server/commands/responses/ircresponseerr_nonicknamegiven.h"
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
    if (ValidateArgs(/*serverclass */))
    {
        serv->setNickname(m_Args[0]);
        return true;
    }
    return false;
}

bool IRCNickCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.empty())
    {
        IRCResponseERR_NONICKNAMEGIVEN* response = dynamic_cast<IRCResponseERR_NONICKNAMEGIVEN*>(
            GetIRCResponsesFactory().CreateResponse(Enum_IRCResponses_ERR_NONICKNAMEGIVEN)
        );
        // send error
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
            }
            // send error
            GetIRCResponsesFactory().DestroyResponse(response);
            return false;
        }
        SetNickname(m_Args[0]);
    }
    return true;
}


}
