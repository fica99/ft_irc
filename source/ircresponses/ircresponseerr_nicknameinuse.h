#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_NICKNAMEINUSE : public IRCResponse
{
public:
    IRCResponseERR_NICKNAMEINUSE();
    virtual ~IRCResponseERR_NICKNAMEINUSE();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetNick(const std::string& nick) { m_Nick = nick; }

private:
    std::string m_Nick;
};

}
