#include <sys/types.h>
#include <sys/socket.h>
#include "ircchannel.h"

namespace ircserv {

IRCChannel::IRCChannel(IRCClient &creator, std::string &name): fprivate(false), owner(creator), _name(name)  {}


Enum_IRCResponses IRCChannel::add_user(IRCClient &nick) {
    if (users.size() >= MAX_CHANNEL_USERS)
        return Enum_IRCResponses_ERR_CHANNELISFULL;

    std::list<std::string>::iterator it;
    for (it = banned.begin(); it != banned.end(); it++) {
        if (*it == nick.nickname) {
            return Enum_IRCResponses_ERR_BANNEDFROMCHAN;
        }
    }
    users.push_back(nick);
    return Enum_IRCResponses_RPL_TOPIC;
}

void IRCChannel::send_all(std::string &mes) {
    for (std::list<IRCClient>::iterator it = users.begin(); it != users.end(); it++) {
        send((*it).fd, mes.c_str(), mes.size(), 0);
    }
}

bool IRCChannel::isMember(std::string &nick) {
    for (std::list<IRCClient>::iterator it = users.begin(); it != users.end(); it++) {
        if ((*it).nickname == nick)
            return true;
    }
    return false;
}
}