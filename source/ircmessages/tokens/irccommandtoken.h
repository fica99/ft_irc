#pragma once

#include <string>

#include "ircmessages/tokens/irctoken.h"

namespace ircserv
{

class IRCCommandToken : public IRCToken
{
public:
    IRCCommandToken();
    virtual ~IRCCommandToken();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    inline void SetCommand(const std::string& command) { m_Command = command; }
    inline void SetCommandNumber(unsigned short int commandNumber) { m_CommandNumber = commandNumber; }
private:
    std::string m_Command;
    unsigned short int m_CommandNumber;
};

}
