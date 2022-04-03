#include "main/precomp.h"

#include "programoptions/commandlineoptionpasswordparams.h"

namespace ircserv
{

CommandLineOptionPasswordParams::CommandLineOptionPasswordParams()
    : CommandLineOptionParams(false, "password", "")
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
    if (arg == nullptr)
    {
        return false;
    }
    return true;
}

}
