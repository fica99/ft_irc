#pragma once

#include <string>

#include "ircserver/ircsocket.h"
#include "ircresponses/ircresponse.h"
#include "ircresponses/ircresponses.h"

namespace ircserv
{

namespace IRCCommandsHelper
{

void SendResponseWithParams(IRCSocket *socket, Enum_IRCResponses responseEnum, const std::string& arg1 = "", const std::string& arg2 = "");
void SendMOTD(IRCSocket *socket, const std::string& server, const std::string& filename);

}

}
