#pragma once

#include <vector>
#include <string>

#include "server/commands/commands/irccommand.h"

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
    bool ProcessCommand(/*serverclass */);

private:
    bool ValidateArgs(/*serverclass */);

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
