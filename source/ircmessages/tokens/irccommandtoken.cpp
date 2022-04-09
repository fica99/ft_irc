#include "main/precomp.h"

#include "ircmessages/tokens/irccommandtoken.h"

namespace ircserv
{

IRCCommandToken::IRCCommandToken(const std::string& rawStr)
    : IRCToken(rawStr)
    , m_CommandEnum(Enum_IRCCommands_Unknown)
{
    Initialize();

    bool result = EnumString<Enum_IRCCommands>::To(m_CommandEnum, rawStr);
    if (!result)
    {
        // send error invalid command
    }
}

void IRCCommandToken::Initialize(void)
{
}


IRCCommandToken::~IRCCommandToken()
{
    Shutdown();
}

void IRCCommandToken::Shutdown(void)
{
}

}
