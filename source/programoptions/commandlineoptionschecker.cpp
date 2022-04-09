#include "main/precomp.h"

#include "programoptions/commandlineoptionschecker.h"

#include "programoptions/commandlineoptions.h"
#include "programoptions/commandlineoptionpasswordparams.h"
#include "programoptions/commandlineoptionportparams.h"
#include "utils/memory.h"

namespace ircserv
{

IMPLEMENT_SIMPLE_SINGLETON(CommandLineOptionsChecker);

static void CommandLineCallback_Port(const char *arg)
{
    std::stringstream ss(arg);
    unsigned short int port;

    ss >> port;
    GetCommandLineOptions().m_Port = port;
}

static void CommandLineCallback_Password(const char *arg)
{
    GetCommandLineOptions().m_Password = arg;
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
        if (params.IsOptional())
        {
            m_Usage += "[";
            if (params.GetFlag() != "")
            {
                m_Usage += params.GetFlag() + " ";
            }
            m_Usage += params.GetValueName();
            m_Usage += "]";
        }
        else
        {
            m_Usage += "<";
            if (params.GetFlag() != "")
            {
                m_Usage += params.GetFlag() + " ";
            }
            m_Usage += params.GetValueName();
            m_Usage += ">";
        }
    }
}

void CommandLineOptionsChecker::Check(int argc, const char *argv[])
{
    size_t j = 0;
    for (size_t i = 1; i < argc; ++i)
    {
        if (j >= m_ParamsCallbacks.size())
        {
            throw std::invalid_argument("More arguments than expected");
        }
        ParamsCallback& paramsCallback = m_ParamsCallbacks[j];
        if (IsValid(argv, i, *(paramsCallback.first)))
        {
            paramsCallback.second(argv[i]);
        }
        ++j;
    }
    for (; j < m_ParamsCallbacks.size(); ++j)
    {
        ParamsCallback& paramsCallback = m_ParamsCallbacks[j];
        if (!paramsCallback.first->IsOptional())
        {
            throw std::invalid_argument("Missing argument");
        }
    }
}

bool CommandLineOptionsChecker::IsValid(const char *argv[], size_t& i, CommandLineOptionParams& params)
{
    if (argv[i] == nullptr)
    {
        return false;
    }

    if (argv[i][0] == '-')
    {
        if (params.IsOptional())
        {
            if (argv[i] != params.GetFlag())
            {
                return false;
            }
        }
        else
        {
            if (argv[i] != params.GetFlag())
            {
                throw std::invalid_argument("Invalid flag");
            }
        }
        ++i;
    }
    else
    {
        if (!params.IsOptional() && params.GetFlag() != "")
        {
            throw std::invalid_argument("Missing flag with argument");
        }
    }
    
    if (argv[i] == nullptr)
    {
        throw std::invalid_argument("Missing argument to flag");
    }

    if (!params.IsValid(argv[i]))
    {
        throw std::invalid_argument("Invalid argument");
    }
    return true;
}

}
