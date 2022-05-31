#pragma once

#include "ircchannel/ircchannel.h"
#include "ircserver/ircsocket.h"
#include "ircclient/ircclient.h"

namespace ircserv
{

namespace IRCCommandsHelper
{

bool IsRegistered(IRCSocket *socket);
void EraseClientFromChannel(IRCClient *client, IRCChannel *channel);
bool IsChannelVisible(IRCChannel *channel);
bool IsAnyChannelVisiable(const std::unordered_set<IRCChannel*>& channels);
bool IsClientVisible(IRCClient *client);

template <class T, typename Container>
bool IsInContainer(const Container& container, const T& el)
{
    return container.find(el) != container.end();
}

}

}
