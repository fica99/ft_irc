#pragma once

#include "utils/singleton.h"

namespace ircserv
{

class IRCParser
{
public:
    IRCParser();
    virtual ~IRCParser();
private:
    void Initialize(void);
    void Shutdown(void);
    DECLARE_SIMPLE_SINGLETON(IRCParser);

};

#define GetIRCParser() IRCParser::GetInstance()

}
