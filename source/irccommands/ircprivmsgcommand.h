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
    bool ProcessCommand(void);

private:
    bool ValidateArgs(void);

private:
    void SendERR_NORECIPIENT(/*serverclass */);
    void SendERR_NOTEXTTOSEND(/*serverclass */);

private:
    inline void SetReceivers(const std::vector<std::string>& receivers) { m_Receivers = receivers; }
    inline void SetTextToBeSent(const std::string& textToBeSent) { m_TextToBeSent = textToBeSent; }

private:
    std::vector<std::string> m_Receivers;
    std::string m_TextToBeSent;
};

}
