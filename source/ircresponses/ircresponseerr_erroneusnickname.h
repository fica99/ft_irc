#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseERR_ERRONEUSNICKNAME : public IRCResponse
{
public:
    IRCResponseERR_ERRONEUSNICKNAME();
    virtual ~IRCResponseERR_ERRONEUSNICKNAME();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetNick(const std::string& nick) { m_Nick = nick; }
    inline const std::string& GetNick(void) const { return m_Nick; }
private:
    std::string m_Nick;
};

}
