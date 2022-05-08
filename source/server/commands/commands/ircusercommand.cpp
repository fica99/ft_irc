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
            m_Username.clear();
            m_Realname.clear();
            return false;
        }
    }
    return true;
}

bool IRCUserCommand::SetUsername(const std::string& username)
{
    size_t pos;

    pos = username.find_first_of(IRCSymbolsDefinition::WHITE_ASCII);
    if (pos != username.npos)
    {
        return false;
    }
    m_Username = username;
    return true;
}

bool IRCUserCommand::SetRealname(const std::string& realname)
{
    size_t pos;

    pos = realname.find_first_of(" ");
    if (pos != realname.npos)
    {
        m_Realname = realname;
    }
    else
    {
        return false;
    }
    return true;
}

}
