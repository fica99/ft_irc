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
    POP_DECLARE_SIMPLE_SINGLETON(CommandLineOptions);
private:
    void Initialize(void);
    void Shutdown(void);

public:
    unsigned short int  m_Port;
    std::string         m_Password;
};

#define popGetCommandLineOptions() CommandLineOptions::GetInstance()


}
