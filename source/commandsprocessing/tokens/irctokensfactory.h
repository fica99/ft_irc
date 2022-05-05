#pragma once

#include <string>

#include "utils/singleton.h"
#include "utils/memory.h"

#include "commandsprocessing/tokens/irctoken.h"
#include "commandsprocessing/tokens/irctokens.h"

namespace ircserv
{

class IRCTokensFactory
{
public:
    IRCTokensFactory();
    virtual ~IRCTokensFactory();
private:
    void Initialize(void);
    void Shutdown(void);
    DECLARE_SIMPLE_SINGLETON(IRCTokensFactory);

public:
    IRCToken* CreateToken(Enum_IRCTokens tokenType);
    void DestroyToken(IRCToken* token);
};

#define GetIRCTokensFactory() IRCTokensFactory::GetInstance()

}
