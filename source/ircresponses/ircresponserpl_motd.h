#pragma once

#include <string>

#include "ircresponses/ircresponse.h"

namespace ircserv
{

class IRCResponseRPL_MOTD : public IRCResponse
{
public:
    IRCResponseRPL_MOTD();
    virtual ~IRCResponseRPL_MOTD();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    std::string GetResponse(void) const;

public:
    inline void SetText(const std::string& text) { m_Text = text; }
    inline const std::string& GetText(void) const { return m_Text; }
    inline void SetNick(const std::string& nick) { m_Nick = nick; }
    inline const std::string& GetNick(void) const { return m_Nick; }
private:
    std::string m_Text;
    std::string m_Nick;
};

}
