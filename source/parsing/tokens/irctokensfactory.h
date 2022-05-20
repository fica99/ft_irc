#pragma once

#include <string>

#include "utils/memory.h"

#include "parsing/tokens/irctoken.h"
#include "parsing/tokens/irctokens.h"

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

public:
    IRCToken* CreateToken(Enum_IRCTokens tokenType);
    void DestroyToken(IRCToken* token);
};

}
