#include "main/precomp.h"

#include "irccommands/ircpartcommand.h"
#include "irccommands/irccommands.h"

#include "parsing/ircparsinghelper.h"
#include "ircresponses/ircresponseerr_needmoreparams.h"
#include "ircresponses/ircresponsesfactory.h"

namespace ircserv
{

IRCPartCommand::IRCPartCommand() : IRCCommand(Enum_IRCCommands_Part)
{
    Initialize();
}

void IRCPartCommand::Initialize(void)
{
}

IRCPartCommand::~IRCPartCommand()
{
    Shutdown();
}

void IRCPartCommand::Shutdown(void)
{
}

bool IRCPartCommand::ProcessCommand(IRCSocket *socket)
{
    if (ValidateArgs(socket))
    {
        return true;
    }
    return false;
}

bool IRCPartCommand::ValidateArgs(IRCSocket *socket)
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
    // else
    // {
    //     if (!IRCParsingHelper::IsChannels(m_Args[0]))
    //     {
    //         return false;
    //     }
    //     SetChannels(IRCParsingHelper::Split(m_Args[0], ","));
    // }
    return true;
}

}
