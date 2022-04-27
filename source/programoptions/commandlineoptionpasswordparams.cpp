#include "main/precomp.h"

#include "programoptions/commandlineoptionpasswordparams.h"

namespace ircserv
{

CommandLineOptionPasswordParams::CommandLineOptionPasswordParams()
    : CommandLineOptionParams("password")
{
    Initialize();
}

void CommandLineOptionPasswordParams::Initialize(void)
{
}

CommandLineOptionPasswordParams::~CommandLineOptionPasswordParams()
{
    Shutdown();
}

void CommandLineOptionPasswordParams::Shutdown(void)
{
}


bool CommandLineOptionPasswordParams::IsValid(const char *arg)
{
    if (arg == NULL)
    {
        return false;
    }
    return true;
}

}
