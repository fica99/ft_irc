#include "main/precomp.h"

#include "irccommands/irckillcommand.h"
#include "irccommands/irccommands.h"

#include "parsing/ircparsinghelper.h"
#include "ircresponses/ircresponseerr_needmoreparams.h"
#include "ircresponses/ircresponsesfactory.h"

namespace ircserv
{

IRCKillCommand::IRCKillCommand() : IRCCommand(Enum_IRCCommands_Kill)
{
    Initialize();
}

void IRCKillCommand::Initialize(void)
{
}

IRCKillCommand::~IRCKillCommand()
{
    Shutdown();
}

void IRCKillCommand::Shutdown(void)
{
}

bool IRCKillCommand::ProcessCommand(void)
{
    if (ValidateArgs())
    {
        return true;
    }
    return false;
}

bool IRCKillCommand::ValidateArgs(void)
{
    // if (m_Args.size() < 2)
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
    // else
    // {
    //     if (!IRCParsingHelper::IsNick(m_Args[0]))
    //     {
    //         return false;
    //     }
    //     SetNickname(m_Args[0]);
    //     SetComment(m_Args[1]);
    // }
    return true;
}
}
