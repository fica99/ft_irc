#pragma once

#include <vector>
#include <string>

#include "irccommands/irccommand.h"

namespace ircserv
{

class IRCPrivmsgCommand : public IRCCommand
{
public:
    IRCPrivmsgCommand();
    virtual ~IRCPrivmsgCommand();
private:
    void Initialize(void);
    void Shutdown(void);

public:
    bool ProcessCommand(IRCSocket *socket);

private:
    bool ValidateArgs(IRCSocket *socket);

private:
    inline void SetReceivers(const std::vector<std::string>& receivers) { m_Receivers = receivers; }
    inline const std::vector<std::string>& GetReceivers(void) const { return m_Receivers; }
    inline void SetTextToBeSent(const std::string& textToBeSent) { m_TextToBeSent = textToBeSent; }
    inline const std::string& GetTextToBeSent(void) const { return m_TextToBeSent; }

private:
    std::vector<std::string> m_Receivers;
    std::string m_TextToBeSent;
};

}
