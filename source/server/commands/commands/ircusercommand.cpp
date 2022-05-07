#include "main/precomp.h"

#include "server/commands/commands/ircusercommand.h"

#include "server/commands/commands/irccommands.h"
#include "server/commands/parsing/ircsymbolsdefinition.h"
#include "server/commands/responses/ircresponseerr_needmoreparams.h"
#include "server/commands/responses/ircresponsesfactory.h"

namespace ircserv
{

IRCUserCommand::IRCUserCommand() : IRCCommand(Enum_IRCCommands_User)
{
    Initialize();
}

void IRCUserCommand::Initialize(void)
{
}

IRCUserCommand::~IRCUserCommand()
{
    Shutdown();
}

void IRCUserCommand::Shutdown(void)
{
}

bool IRCUserCommand::ProcessCommand(/*serverclass */)
{
    if (ValidateArgs(/*serverclass */))
    {
        return true;
    }
    return false;
}

bool IRCUserCommand::ValidateArgs(/*serverclass */)
{
    if (m_Args.size() < 4)
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
    else
    {
        if (!SetUsername(m_Args[0]) || !SetRealname(m_Args[3]))
        {
            return false;
        }
    }
    return true;
}

bool IRCUserCommand::SetUsername(const std::string& arg)
{
    size_t pos;

    pos = arg.find_first_of(IRCSymbolsDefinition::WHITE_ASCII);
    if (pos != arg.npos)
    {
        return false;
    }
    m_Username = arg;
    return true;
}

bool IRCUserCommand::SetRealname(const std::string& arg)
{
    size_t pos;

    pos = arg.find_first_of(":");
    if (pos == 0)
    {
        m_Username = arg;
        m_Username.erase(0, 1);
    }
    else
    {
        return false;
    }
    return true;
}

}
