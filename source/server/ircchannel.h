#include "main/precomp.h"
#include "ircclient.h"

namespace ircserv
{

class IRCChannel {
public:
    IRCChannel(IRCClient &creator);
    
    void add_op(IRCClient &nick, std::string &pass);
    void add_user(IRCClient &nick);
    void make_private();

private:
    IRCClient owner;
    std::list<IRCClient> users;
    std::list<IRCClient> ops;
    std::list<IRCClient> banned;
    bool fprivate; 
};

}