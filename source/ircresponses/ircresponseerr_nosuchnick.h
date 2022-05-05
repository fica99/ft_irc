#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_NOSUCHNICK : public IRCResponse
{
public:
    IRCResponseERR_NOSUCHNICK();
    virtual ~IRCResponseERR_NOSUCHNICK();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetNickname(const std::string& nickname) { m_Nickname = nickname; }

private:
    std::string m_Nickname;
};

}
