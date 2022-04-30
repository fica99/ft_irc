#include "main/precomp.h"

#include "programoptions/commandlineoptionparams.h"

namespace ircserv
{

CommandLineOptionParams::CommandLineOptionParams(const std::string& valueName)
    : m_ValueName(valueName)
{
    Initialize();
}

void CommandLineOptionParams::Initialize(void)
{
}

CommandLineOptionParams::~CommandLineOptionParams()
{
    Shutdown();
}

void CommandLineOptionParams::Shutdown(void)
{
}

}
