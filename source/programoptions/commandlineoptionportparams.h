#pragma once

#include "programoptions/commandlineoptionparams.h"

namespace ircserv
{

class CommandLineOptionPortParams : public CommandLineOptionParams
{
public:
    CommandLineOptionPortParams();
    ~CommandLineOptionPortParams();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool IsValid(const char *arg);

private:
    const unsigned short int MIN_PORT;
    const unsigned short int MAX_PORT;
};


}

