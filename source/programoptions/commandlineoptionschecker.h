#pragma once

#include <vector>
#include <utility>

#include "programoptions/commandlineoptionparams.h"
#include "utils/singleton.h"

namespace ircserv
{

class CommandLineOptionsChecker
{
private:
    typedef std::pair<CommandLineOptionParams*, void(*)(const char *)> ParamsCallback;
public:
    CommandLineOptionsChecker();
    virtual ~CommandLineOptionsChecker();
private:
    void Initialize(void);
    void Shutdown(void);
    POP_DECLARE_SIMPLE_SINGLETON(CommandLineOptionsChecker);

private:
    void SetUsage(void);
public:
    inline const std::string& GetUsage(void) const { return m_Usage; }

public:
    void Check(int argc, const char *argv[]);
private:
    bool IsValid(const char *argv[], size_t& i, CommandLineOptionParams& params);

private:
    std::vector<ParamsCallback> m_ParamsCallbacks;
    std::string m_Usage;
};

#define popGetCommandLineOptionsChecker() CommandLineOptionsChecker::GetInstance()

}
