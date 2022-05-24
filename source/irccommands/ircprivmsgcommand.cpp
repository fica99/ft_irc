#include "main/precomp.h"

#include "irccommands/ircprivmsgcommand.h"
#include "irccommands/irccommands.h"

#include "parsing/ircparsinghelper.h"
#include "ircresponses/ircresponseerr_norecipient.h"
#include "ircresponses/ircresponseerr_notexttosend.h"
#include "ircresponses/ircresponsesfactory.h"

namespace ircserv
{

IRCPrivmsgCommand::IRCPrivmsgCommand() : IRCCommand(Enum_IRCCommands_Privmsg)
{
    Initialize();
}

void IRCPrivmsgCommand::Initialize(void)
{
}

IRCPrivmsgCommand::~IRCPrivmsgCommand()
{
    Shutdown();
}

void IRCPrivmsgCommand::Shutdown(void)
{
}

bool IRCPrivmsgCommand::ProcessCommand(IRCSocket *socket)
{
    if (ValidateArgs())
    {
        return true;
    }
    return false;
}

bool IRCPrivmsgCommand::ValidateArgs(void)
{
    // if (m_Args.empty())
    // {
    //     SendERR_NORECIPIENT();
    //     return false;
    // }
    // else if (m_Args.size() < 2)
    // {
    //     SendERR_NOTEXTTOSEND();
    //     return false;
    // }
    // else
    // {
    //     std::vector<std::string> receivers = IRCParsingHelper::Split(m_Args[0], ",");
    //     if (receivers.empty())
    //     {
    //         SendERR_NORECIPIENT();
    //         return false;
    //     }
    //     for (size_t i = 0; i < receivers.size(); ++i)
    //     {
    //         if (!IRCParsingHelper::IsNick(receivers[i]) && !!IRCParsingHelper::IsChannel(receivers[i]))
    //         {
    //             return false;
    //         }
    //     }
    //     if (m_Args[1].empty())
    //     {
    //         SendERR_NOTEXTTOSEND();
    //         return false;
    //     }
    //     SetReceivers(receivers);
    //     SetTextToBeSent(m_Args[1]);

    // }

    return true;
}

void IRCPrivmsgCommand::SendERR_NORECIPIENT(/*serverclass */)
{
    // IRCResponseERR_NORECIPIENT* response = dynamic_cast<IRCResponseERR_NORECIPIENT*>(
    //     GetIRCResponsesFactory().CreateResponse(Enum_IRCResponses_ERR_NORECIPIENT)
    // );
    // if (response != NULL)
    // {
    //     response->SetCommand(EnumString<Enum_IRCCommands>::From(GetCommandEnum()));
    // }
    // // send response
    // GetIRCResponsesFactory().DestroyResponse(response);
}

void IRCPrivmsgCommand::SendERR_NOTEXTTOSEND(/*serverclass */)
{
    // IRCResponseERR_NOTEXTTOSEND* response = dynamic_cast<IRCResponseERR_NOTEXTTOSEND*>(
    //     GetIRCResponsesFactory().CreateResponse(Enum_IRCResponses_ERR_NOTEXTTOSEND)
    // );
    // // send response
    // GetIRCResponsesFactory().DestroyResponse(response);
}



}
