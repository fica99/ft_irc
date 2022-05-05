#pragma once

#include <string>

#include "server/commands/parsing/tokens/irctoken.h"

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
    inline const std::string& GetCommand(void) const { return m_Command; }
    inline void SetCommandNumber(unsigned short int commandNumber) { m_CommandNumber = commandNumber; }
    inline unsigned short int GetCommandNumber(void) const { return m_CommandNumber; }
private:
    std::string m_Command;
    unsigned short int m_CommandNumber;
};

}
