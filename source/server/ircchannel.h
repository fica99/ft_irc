#include "main/precomp.h"
#include "ircclient.h"
#include "server/commands/responses/ircresponses.h"
#define MAX_CHANNEL_USERS 100

namespace ircserv
{

class IRCChannel {
public:
    IRCChannel(IRCClient &creator, std::string &name);
    
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
private: 
    IRCClient owner;
    std::list<IRCClient> users;
    std::list<IRCClient> ops;
    std::list<std::string> banned;
    bool fprivate; 
};

}