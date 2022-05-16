#pragma once

#include <vector>
#include <utility>

#include "programoptions/commandlineoptionparams.h"

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

private:
    void SetUsage(void);

public:
    void Check(int argc, const char *argv[]);

public:
    inline static const std::string& GetUsage(void) { return m_Usage; }

private:
    std::vector<ParamsCallback> m_ParamsCallbacks;
    static std::string m_Usage;
};

}
