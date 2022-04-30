#pragma once

#include "programoptions/commandlineoptionparams.h"

namespace ircserv
{

class CommandLineOptionPasswordParams : public CommandLineOptionParams
{
public:
    CommandLineOptionPasswordParams();
    ~CommandLineOptionPasswordParams();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool IsValid(const char *arg);
};


}
