#include "main/precomp.h"

#include "irccommands/irckickcommand.h"
#include "irccommands/irccommands.h"

#include "parsing/ircparsinghelper.h"
#include "ircresponses/ircresponseerr_needmoreparams.h"
#include "ircresponses/ircresponsesfactory.h"

namespace ircserv
{

IRCKickCommand::IRCKickCommand() : IRCCommand(Enum_IRCCommands_Kick)
{
    Initialize();
}

void IRCKickCommand::Initialize(void)
{
}

IRCKickCommand::~IRCKickCommand()
{
    Shutdown();
}

void IRCKickCommand::Shutdown(void)
{
}

bool IRCKickCommand::ProcessCommand(IRCSocket *socket)
{
    if (ValidateArgs())
    {
        return true;
    }
    return false;
}

bool IRCKickCommand::ValidateArgs(void)
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
    //     // server->send(response->GetResponse())
    //     // send response
    //     GetIRCResponsesFactory().DestroyResponse(response);
    //     return false;
    // }
    // else
    // {
    //     if (!IRCParsingHelper::IsChannel(m_Args[0]) || !IRCParsingHelper::IsUser(m_Args[1]))
    //     {
    //         return false;
    //     }
    //     SetChannel(m_Args[0]);
    //     SetUser(m_Args[1]);
    //     if (m_Args.size() > 2)
    //     {
    //         SetComment(m_Args[2]);
    //     }
    // }
    return true;
}
}
