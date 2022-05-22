#pragma once

#include <cstdint>
#include <string>
#include "utils/singleton.h"

namespace ircserv
{

class CommandLineOptions
{
public:
    CommandLineOptions();
    virtual ~CommandLineOptions();
    DECLARE_SIMPLE_SINGLETON(CommandLineOptions);
private:
    void Initialize(void);
    void Shutdown(void);

public:
    inline void SetPort(uint16_t port) { m_Port = port; }
    inline uint16_t GetPort(void) const { return m_Port; }
    inline void SetPassword(const std::string& password) { m_Password = password; }
    inline const std::string& GetPassword(void) const { return m_Password; }
private:
    uint16_t    m_Port;
    std::string m_Password;
};

#define GetCommandLineOptions() CommandLineOptions::GetInstance()


}
