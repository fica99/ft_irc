#pragma once

#include <string>

#include "utils/singleton.h"
#include "utils/memory.h"

#include "ircmessages/tokens/irctoken.h"
#include "ircmessages/tokens/ircprefixtoken.h"
#include "ircmessages/tokens/irccommandtoken.h"

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
    inline IRCToken* CreateToken(const std::string& rawStr) { return New(IRCToken)(rawStr); }

    inline IRCToken* CreatePrefixToken(
        const std::string& rawStr,
        const std::string& prefix = ":"
    ) { return New(IRCPrefixToken)(rawStr, prefix); }

    inline IRCToken* CreateCommandToken(const std::string& rawStr) { return New(IRCCommandToken)(rawStr); }
};

#define GetIRCTokensFactory() IRCTokensFactory::GetInstance()

}
