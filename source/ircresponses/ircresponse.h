#pragma once

#include <string>

#include "ircresponses/ircresponses.h"
#include "ircserver/ircsocket.h"

namespace ircserv
{

class IRCResponse
{
public:
    IRCResponse(Enum_IRCResponses responseEnum);
    virtual ~IRCResponse();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    virtual std::string GetResponse(void) const = 0;

public:
    inline void GetResponseEnum(Enum_IRCResponses responseEnum) { m_ResponseEnum = responseEnum; }
    inline Enum_IRCResponses GetResponseEnum(void) const { return m_ResponseEnum; }
    inline void SetPrefix(const std::string& prefix) { m_Prefix = ":" + prefix; }
    inline const std::string& GetPrefix(void) const { return m_Prefix; }
    inline void SetNickname(const std::string& nickname) { m_Nickname = nickname; }
    inline const std::string& GetNickname(void) const { return m_Nickname; }

private:
    Enum_IRCResponses m_ResponseEnum;
    std::string m_Prefix; 
    std::string m_Nickname;
};

}
