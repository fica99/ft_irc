#include "main/precomp.h"

#include "server/commands/commands/ircpasscommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/responses/ircresponseerr_needmoreparams.h"
#include "server/commands/responses/ircresponsesfactory.h"

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

bool IRCPassCommand::ProcessCommand(IRCServer *serv)
{
    if (ValidateArgs(serv))
    {
        return true;
    }
    return false;
}

bool IRCPassCommand::ValidateArgs(IRCServer *serv)
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
    SetPassword(m_Args[0]);
    return true;
}

}
