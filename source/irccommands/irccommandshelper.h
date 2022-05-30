#pragma once

#include "ircchannel/ircchannel.h"
#include "ircserver/ircsocket.h"
#include "ircclient/ircclient.h"

namespace ircserv
{

namespace IRCCommandsHelper
{

bool IsRegistered(IRCSocket *socket);
bool IsBannedByChannel(IRCClient *client, IRCChannel *channel);
void EraseClientFromChannel(IRCClient *client, IRCChannel *channel);

}

}
