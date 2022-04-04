#include "main/precomp.h"

#include "programoptions/commandlineoptionparams.h"

namespace ircserv
{

CommandLineOptionParams::CommandLineOptionParams(
    bool isOptional,
    const std::string& valueName,
    const std::string& flag
    ) : m_IsOptional(isOptional)
      , m_ValueName(valueName)
      , m_Flag(flag)
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
