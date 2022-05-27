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
    void Send(IRCSocket *socket);
    virtual std::string GetResponse(void) const = 0;

public:
    inline void SetPrefix(const std::string& prefix) { m_Prefix = ":" + prefix; }

public:
    inline Enum_IRCResponses GetResponseEnum(void) const { return m_ResponseEnum; }
protected:
    inline const std::string& GetPrefix(void) const { return m_Prefix; }

private:
    Enum_IRCResponses m_ResponseEnum;
    std::string m_Prefix; 
};

}
