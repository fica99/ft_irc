#include "main/precomp.h"

#include "irccommands/ircopercommand.h"
#include "irccommands/irccommands.h"

#include "parsing/ircparsinghelper.h"
#include "ircresponses/ircresponseerr_needmoreparams.h"
#include "ircresponses/ircresponserpl_youreoper.h"
#include "ircresponses/ircresponsesfactory.h"

namespace ircserv
{

IRCOperCommand::IRCOperCommand() : IRCCommand(Enum_IRCCommands_Oper)
{
    Initialize();
}

void IRCOperCommand::Initialize(void)
{
}

IRCOperCommand::~IRCOperCommand()
{
    Shutdown();
}

void IRCOperCommand::Shutdown(void)
{
}

bool IRCOperCommand::ProcessCommand(IRCSocket *socket)
{
    if (ValidateArgs(socket))
    {
        // IRCResponseRPL_YOUREOPER* response = dynamic_cast<IRCResponseRPL_YOUREOPER*>(
        //     GetIRCResponsesFactory().CreateResponse(Enum_IRCResponses_RPL_YOUREOPER)
        // );
        // // send response
        // GetIRCResponsesFactory().DestroyResponse(response);
        return true;
    }
    return false;
}

bool IRCOperCommand::ValidateArgs(IRCSocket *socket)
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
    //     if (!IRCParsingHelper::IsUser(m_Args[0]))
    //     {
    //         return false;
    //     }
    //     SetUser(m_Args[1]);
    //     SetPassword(m_Args[1]);
    // }
    return true;
}

}
