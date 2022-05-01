#pragma once

#include <string>

#include "ircresponses/ircresponses.h"

namespace ircserv
{

class IRCResponse
{
public:
    IRCResponse(Enum_IRCCResponses responseType = Enum_IRCResponses_Unknown,
            const std::string& prefix = "",
            const std::string& delimeter = " ");
    virtual ~IRCResponse();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    const std::string& GetResponse() const { return m_Response; }
protected:
    virtual void InitResponse(void) = 0;

protected: 
    const Enum_IRCCResponses m_ResponseType;
    const std::string m_Prefix;
    const std::string m_Delimeter;
    std::string m_Response;
};

}
