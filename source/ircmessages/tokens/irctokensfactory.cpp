#include "main/precomp.h"

#include "ircmessages/tokens/irctokensfactory.h"

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

}
