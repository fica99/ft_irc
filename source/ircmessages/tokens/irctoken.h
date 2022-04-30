#pragma once

#include <string>

namespace ircserv
{

class IRCToken
{
public:
    IRCToken(const std::string& rawStr);
    virtual ~IRCToken();
private:
    void Initialize(void);
    void Shutdown(void);
public:
    inline const std::string& GetRawStr(void) const { return m_RawStr; }
private:
    std::string m_RawStr;
};

}
