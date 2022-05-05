#include "main/precomp.h"

#include "server/commands/parsing/tokens/irctokensfactory.h"

#include "server/commands/parsing/tokens/ircargtoken.h"
#include "server/commands/parsing/tokens/irccommandtoken.h"
#include "server/commands/parsing/tokens/ircprefixtoken.h"

namespace ircserv
{

IRCTokensFactory::IRCTokensFactory()
{
    Initialize();
}

void IRCTokensFactory::Initialize(void)
{
}

IRCTokensFactory::~IRCTokensFactory()
{
    Shutdown();
}

void IRCTokensFactory::Shutdown(void)
{
}

IRCToken* IRCTokensFactory::CreateToken(Enum_IRCTokens tokenType)
{
    IRCToken* token = NULL;
    switch (tokenType)
    {
        case Enum_IRCTokens_Prefix:
            token = New(IRCPrefixToken)();
            break;
        case Enum_IRCTokens_Command:
            token = New(IRCCommandToken)();
            break;
        case Enum_IRCTokens_Arg:
            token = New(IRCArgToken)();
            break;
        default:
            token = NULL;
            break;
    }
    return token;
}


void IRCTokensFactory::DestroyToken(IRCToken* token)
{ 
    if (token != NULL)
    {
        Delete(token);
    }
}

}
