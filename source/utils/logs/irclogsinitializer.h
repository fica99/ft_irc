#pragma once

#include "utils/singleton.h"

namespace ircserv
{

class IRCLogsInitializer
{
public:
    IRCLogsInitializer();
    virtual ~IRCLogsInitializer();
private:
    void Initialize(void);
    void Shutdown(void);
    DECLARE_SIMPLE_SINGLETON(IRCLogsInitializer);
};

#define GetIRCLogsInitializer() IRCLogsInitializer::GetInstance()

}
