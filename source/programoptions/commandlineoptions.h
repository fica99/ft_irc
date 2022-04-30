#pragma once

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
    inline void SetPort(unsigned short int port) { m_Port = port; }
    inline unsigned short int GetPort(void) const { return m_Port; }
    inline void SetPassword(const std::string& password) { m_Password = password; }
    inline const std::string& GetPassword(void) const { return m_Password; }
private:
    unsigned short int  m_Port;
    std::string         m_Password;
};

#define GetCommandLineOptions() CommandLineOptions::GetInstance()


}
