#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseRPL_MOTDSTART : public IRCResponse
{
public:
    IRCResponseRPL_MOTDSTART();
    virtual ~IRCResponseRPL_MOTDSTART();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetServer(const std::string& server) { m_Server = server; }

private:
    std::string m_Server;
};

}
