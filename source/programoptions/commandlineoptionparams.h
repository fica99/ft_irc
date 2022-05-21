#pragma once

#include <string>

namespace ircserv
{

class CommandLineOptionParams
{
public:
    CommandLineOptionParams(const std::string& valueName);
    virtual ~CommandLineOptionParams();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    virtual bool IsValid(const char *arg) = 0;
    inline const std::string& GetValueName(void) const { return m_ValueName; }

protected:
    std::string m_ValueName;
};

}
