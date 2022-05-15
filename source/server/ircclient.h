#pragma once

#include <string>

namespace ircserv
{

struct IRCClient 
{
    IRCClient();
    virtual ~IRCClient();
    std::string obuf;
    std::string inbuf;
    std::string nickname;
    std::string prefix;   //not used after registration
    int errcode;
    bool registered;
};

}
