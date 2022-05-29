#pragma once

#include <string>

#include "irccommands/irccommands.h"
#include "ircresponses/ircresponses.h"
#include "ircserver/ircsocket.h"

namespace ircserv
{

namespace IRCCommandsHelper
{

void SendResponseWithoutParams(IRCSocket *socket, Enum_IRCResponses responseEnum);
void SendERR_NEEDMOREPARAMS(IRCSocket *socket, Enum_IRCCommands commandEnum);
void SendERR_ERRONEUSNICKNAME(IRCSocket *socket, const std::string& nick);
void SendERR_NICKNAMEINUSE(IRCSocket *socket, const std::string& nick);
void SendRPL_MOTDSTART(IRCSocket *socket, const std::string server);
void SendRPL_MOTD(IRCSocket *socket, const std::string& filename);
void SendMOTD(IRCSocket *socket, const std::string server, const std::string& filename);
void SendERR_UNKNOWNCOMMAND(IRCSocket *socket, const std::string& command);
void SendResponseWithServerName(IRCSocket *socket, Enum_IRCResponses responseEnum, const std::string& channelName);
void SendResponseWithTopic(IRCSocket *socket, const std::string& channelName, const std::string& topic);


}

}
