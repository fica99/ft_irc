#include "main/precomp.h"

#include "irccommands/ircnickcommand.h"

#include "irccommands/irccommands.h"
//#include <map>

namespace ircserv
{

IRCNickCommand::IRCNickCommand()
{
    Initialize();
}

void IRCNickCommand::Initialize(void)
{
    SetCommandType(Enum_IRCCommands_Nick);
}

IRCNickCommand::~IRCNickCommand()
{
    Shutdown();
}

void IRCNickCommand::Shutdown(void)
{
}

bool IRCNickCommand::ProcessCommand(Server *s, std::pair<const int, Client> client)
{
    std::map<int, Client>::iterator it;
    std::string &arg = m_Args[0];
    
    if (arg == "") {
        this->err = ERR_NONICKNAMEGIVEN;
        return false;
    }

    for (it = s->clients.begin(); it != s->clients.end(); it++) {
        if (it->second.nickname == arg) {
            this->err = ERR_NICKNAMEINUSE;
            return false;
        }
    }
    client.second.setNickname(arg);
    return true;
}


}
