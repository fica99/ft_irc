#include "main/precomp.h"

#include "ircresponses/ircresponserpl_welcome.h"

#include "ircresponses/ircresponses.h"


namespace ircserv
{

IRCResponseRPL_WELCOME::IRCResponseRPL_WELCOME(
        const std::string& prefix,
        const std::string& delimeter)
    : IRCResponse(Enum_IRCResponses_RPL_WELCOME, prefix, delimeter)
{
    Initialize();
}

void IRCResponseRPL_WELCOME::Initialize(void)
{
}

IRCResponseRPL_WELCOME::~IRCResponseRPL_WELCOME()
{
    Shutdown();
}

void IRCResponseRPL_WELCOME::Shutdown(void)
{
}

void IRCResponseRPL_WELCOME::InitResponse(void)
{
    if (!m_Prefix.empty())
    {
        m_Response = m_Prefix + m_Delimeter;
    }
    else
    {
        m_Response = "";
    }
    m_Response += EnumString<Enum_IRCCResponses>::From(m_ResponseType) + m_Delimeter;
    m_Response += "Welcome to the Internet Relay Network " + m_Nick + "!" + m_User + "@" + m_Host;
}

void IRCResponseRPL_WELCOME::SetNick(const std::string& nick)
{
    m_Nick = nick;
    InitResponse();
}

void IRCResponseRPL_WELCOME::SetUser(const std::string& user)
{
    m_User = user;
    InitResponse();
}
void IRCResponseRPL_WELCOME::SetHost(const std::string& host)
{
    m_Host = host;
    InitResponse();
}

}
