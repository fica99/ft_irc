#include "main/precomp.h"

#include "programoptions/commandlineoptions.h"

namespace ircserv
{

POP_IMPLEMENT_SIMPLE_SINGLETON(CommandLineOptions);

CommandLineOptions::CommandLineOptions()
{
    POP_IMPLEMENT_SIMPLE_SINGLETON_CONSTRUCTOR();
    Initialize();
}

void CommandLineOptions::Initialize()
{
}

CommandLineOptions::~CommandLineOptions()
{
    Shutdown();

    POP_IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void CommandLineOptions::Shutdown()
{
}

}
