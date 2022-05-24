#include "main/precomp.h"

#include "irccommands/ircpasscommand.h"
#include "irccommands/irccommands.h"

#include "ircresponses/ircresponseerr_needmoreparams.h"
#include "ircresponses/ircresponsesfactory.h"

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
    if (ValidateArgs())
    {
        return true;
    }
    return false;
}

bool IRCPassCommand::ValidateArgs(void)
{
    // if (m_Args.empty())
    // {
    //     IRCResponseERR_NEEDMOREPARAMS* response = dynamic_cast<IRCResponseERR_NEEDMOREPARAMS*>(
    //         GetIRCResponsesFactory().CreateResponse(Enum_IRCResponses_ERR_NEEDMOREPARAMS)
    //     );
    //     if (response != NULL)
    //     {
    //         response->SetCommand(EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
    //     }
    //     // send response
    //     GetIRCResponsesFactory().DestroyResponse(response);
    //     return false;
    // }
    // SetPassword(m_Args[0]);
    return true;
}

}
