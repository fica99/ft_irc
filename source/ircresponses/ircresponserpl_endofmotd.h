#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseRPL_ENDOFMOTD : public IRCResponse
{
public:
    IRCResponseRPL_ENDOFMOTD();
    virtual ~IRCResponseRPL_ENDOFMOTD();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;
    inline void SetNick(const std::string& nick) { m_Nick = nick; }
    inline const std::string& GetNick(void) const { return m_Nick; }

private:
    std::string m_Nick;
};

}
