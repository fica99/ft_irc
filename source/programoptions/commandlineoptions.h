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
    unsigned short int  Port;
    std::string         Password;
};

#define GetCommandLineOptions() CommandLineOptions::GetInstance()


}
