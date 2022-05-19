#pragma once

#include "server/ircclient.h"
#include "server/commands/responses/ircresponses.h"

namespace ircserv
{

class IRCChannel
{
public:
    IRCChannel(IRCClient &creator, const std::string &name);
    
    std::string _name;

    bool isMember(std::string &nick);
    void add_op(IRCClient &nick, std::string &pass);
    Enum_IRCResponses add_user(IRCClient &nick);
    void make_private() { fprivate = true; }
    void make_public() { fprivate = false; }
    bool IsPrivate() { return fprivate; }
    IRCClient& get_owner() { return owner; }
    void ban_user(std::string &nick) { banned.push_back(nick); };
    void send_all(std::string &mes);
    std::string getTopic() { return m_Topic; }
private:
    std::string m_Topic;
    IRCClient owner;
    std::list<IRCClient> users;
    std::list<IRCClient> ops;
    std::list<std::string> banned;
    bool fprivate; 
};

}
