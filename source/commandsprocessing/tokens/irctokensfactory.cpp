#include "main/precomp.h"

#include "commandsprocessing/tokens/irctokensfactory.h"

#include "commandsprocessing/tokens/ircargtoken.h"
#include "commandsprocessing/tokens/irccommandtoken.h"
#include "commandsprocessing/tokens/ircprefixtoken.h"

namespace ircserv
{

IMPLEMENT_SIMPLE_SINGLETON(IRCTokensFactory);

IRCTokensFactory::IRCTokensFactory()
{
    IMPLEMENT_SIMPLE_SINGLETON_CONSTRUCTOR();

    Initialize();
}

void IRCTokensFactory::Initialize(void)
{
}

IRCTokensFactory::~IRCTokensFactory()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
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
