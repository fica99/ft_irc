#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseRPL_WELCOME : public IRCResponse
{
public:
    IRCResponseRPL_WELCOME(const std::string& prefix = "", const std::string& delimeter = " ");
    virtual ~IRCResponseRPL_WELCOME();
private:
    void Initialize(void);
    void Shutdown(void);

private:
    void InitResponse(void);

public:
    void SetNick(const std::string& nick);
    void SetUser(const std::string& user);
    void SetHost(const std::string& host);

private:
    std::string m_Nick;
    std::string m_User;
    std::string m_Host;
};

}
