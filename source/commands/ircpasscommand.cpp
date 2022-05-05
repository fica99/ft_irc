#include "main/precomp.h"

#include "commands/ircpasscommand.h"

#include "commands/irccommands.h"
#include "responses/ircresponseerr_needmoreparams.h"
#include "responses/ircresponsesfactory.h"

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

bool IRCPassCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCPassCommand::ValidateArgs(/*serverclass */)
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
        GetIRCResponsesFactory().DestroyResponse(response);
        return false;
    }
    return true;
}

}
