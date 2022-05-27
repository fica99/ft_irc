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
    inline const std::string& GetServer(void) const { return m_Server; }
    inline void SetNick(const std::string& nick) { m_Nick = nick; }
    inline const std::string& GetNick(void) const { return m_Nick; }

private:
    std::string m_Server;
    std::string m_Nick;
};

}
