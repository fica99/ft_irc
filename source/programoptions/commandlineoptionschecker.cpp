#include "main/precomp.h"

#include "programoptions/commandlineoptionschecker.h"

#include "programoptions/commandlineoptions.h"
#include "programoptions/commandlineoptionpasswordparams.h"
#include "programoptions/commandlineoptionportparams.h"
#include "utils/memory.h"

namespace ircserv
{

IMPLEMENT_SIMPLE_SINGLETON(CommandLineOptionsChecker);
std::string CommandLineOptionsChecker::m_Usage;

static void CommandLineCallback_Port(const char *arg)
{
    std::istringstream ss(arg);
    unsigned short int port;

    ss >> port;
    GetCommandLineOptions().SetPort(port);
}

static void CommandLineCallback_Password(const char *arg)
{
    GetCommandLineOptions().SetPassword(arg);
}

CommandLineOptionsChecker::CommandLineOptionsChecker()
{
    IMPLEMENT_SIMPLE_SINGLETON_CONSTRUCTOR();

    Initialize();
}

void CommandLineOptionsChecker::Initialize(void)
{
    m_ParamsCallbacks.push_back(std::make_pair(New(CommandLineOptionPortParams)(), CommandLineCallback_Port));
    m_ParamsCallbacks.push_back(std::make_pair(New(CommandLineOptionPasswordParams)(), CommandLineCallback_Password));

    SetUsage();
}

CommandLineOptionsChecker::~CommandLineOptionsChecker()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void CommandLineOptionsChecker::Shutdown(void)
{
    for (size_t i = 0; i < m_ParamsCallbacks.size(); ++i)
    {
        Delete(m_ParamsCallbacks[i].first);
    }
}

void CommandLineOptionsChecker::SetUsage(void)
{
    m_Usage = "Usage: ircserv";
    for (size_t i = 0; i < m_ParamsCallbacks.size(); ++i)
    {
        m_Usage += " ";
        CommandLineOptionParams& params = *(m_ParamsCallbacks[i].first);
        m_Usage += params.GetValueName();
    }
}

void CommandLineOptionsChecker::Check(int argc, const char *argv[])
{
    if (argc - 1 != m_ParamsCallbacks.size())
    {
        throw std::invalid_argument("Expected other number of commandline arguments");
    }
    for (size_t i = 1; i < argc; ++i)
    {
        ParamsCallback& paramsCallback = m_ParamsCallbacks[i - 1];
        CommandLineOptionParams* params = paramsCallback.first;
        if (params && params->IsValid(argv[i]))
        {
            paramsCallback.second(argv[i]);
        }
        else
        {
            throw std::invalid_argument(std::string("Invalid argument: ") + argv[i]);
        }
    }
}

}
