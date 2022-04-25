#pragma once

#include <string>

namespace ircserv
{

class CommandLineOptionParams
{
public:
    CommandLineOptionParams(
        bool isOptional = true,
        const std::string& valueName = "",
        const std::string& flag = ""
    );
    virtual ~CommandLineOptionParams();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    virtual bool IsValid(const char *arg) = 0;
    inline bool IsOptional(void) const { return m_IsOptional; }
    inline const std::string& GetValueName(void) const { return m_ValueName; }
    inline const std::string& GetFlag(void) const { return m_Flag; }

protected:
    bool        m_IsOptional;
    std::string m_ValueName;
    std::string m_Flag;
};

}
