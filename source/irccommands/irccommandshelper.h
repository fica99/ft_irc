#pragma once

#include <string>

#include "ircserver/ircsocket.h"
#include "ircresponses/ircresponse.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

namespace IRCCommandsHelper
{

void SendResponse(IRCSocket *socket, IRCResponse *response);
void SendResponseWithParams(IRCSocket *socket, Enum_IRCResponses responseEnum, const std::string& arg1 = "", const std::string& arg2 = "");
void SendMOTD(IRCSocket *socket, const std::string& server, const std::string& filename);
void SendTopic(IRCSocket *socket, const std::string& channel, const std::string& topic);
void SendChannelNames(IRCSocket *socket, const std::string& channelName);

}

}
