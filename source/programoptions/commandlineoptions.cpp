#include "main/precomp.h"

#include "programoptions/commandlineoptions.h"

namespace ircserv
{

IMPLEMENT_SIMPLE_SINGLETON(CommandLineOptions);

CommandLineOptions::CommandLineOptions()
{
    IMPLEMENT_SIMPLE_SINGLETON_CONSTRUCTOR();
    Initialize();
}

void CommandLineOptions::Initialize()
{
}

CommandLineOptions::~CommandLineOptions()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void CommandLineOptions::Shutdown()
{
}

}
