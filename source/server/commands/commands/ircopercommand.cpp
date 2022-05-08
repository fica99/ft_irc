#include "main/precomp.h"

#include "server/commands/commands/ircopercommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/parsing/ircsymbolsdefinition.h"
#include "server/commands/responses/ircresponseerr_needmoreparams.h"
#include "server/commands/responses/ircresponserpl_youreoper.h"
#include "server/commands/responses/ircresponsesfactory.h"

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

bool IRCOperCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCOperCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.size() < 2)
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
    SetUser(m_Args[0]);
    m_Password = m_Args[1];
    IRCResponseRPL_YOUREOPER* response = dynamic_cast<IRCResponseRPL_YOUREOPER*>(
        GetIRCResponsesFactory().CreateResponse(Enum_IRCResponses_RPL_YOUREOPER)
    );
    // send response
    GetIRCResponsesFactory().DestroyResponse(response);
    return true;
}

bool IRCOperCommand::SetUser(const std::string& arg)
{
    size_t pos;

    pos = arg.find_first_of(IRCSymbolsDefinition::WHITE_ASCII);
    if (pos != arg.npos)
    {
        return false;
    }
    m_User = arg;
    return true;
}

}
