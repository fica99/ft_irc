#include "main/precomp.h"

#include "ircmessages/parser/ircparser.h"

namespace ircserv
{

IMPLEMENT_SIMPLE_SINGLETON(IRCParser);

IRCParser::IRCParser()
{
    IMPLEMENT_SIMPLE_SINGLETON_CONSTRUCTOR();

    Initialize();
}

void IRCParser::Initialize(void)
{
}

IRCParser::~IRCParser()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void IRCParser::Shutdown(void)
{
}

}
