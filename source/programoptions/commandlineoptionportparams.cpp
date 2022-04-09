#include "main/precomp.h"

#include "programoptions/commandlineoptionportparams.h"

namespace ircserv
{

CommandLineOptionPortParams::CommandLineOptionPortParams()
    : CommandLineOptionParams(false, "port", "")
    , MIN_PORT(std::numeric_limits<unsigned short int>::min() + 1)
    , MAX_PORT(std::numeric_limits<unsigned short int>::max())
{
    Initialize();
}

void CommandLineOptionPortParams::Initialize(void)
{
}

CommandLineOptionPortParams::~CommandLineOptionPortParams()
{
    Shutdown();
}

void CommandLineOptionPortParams::Shutdown(void)
{
}


bool CommandLineOptionPortParams::IsValid(const char *arg)
{
    if (arg == NULL)
    {
        return false;
    }
    std::stringstream ss(arg);
    int port;

    ss >> port;
    return ss.eof() && port > MIN_PORT && port <= MAX_PORT;
}


}
