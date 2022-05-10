#pragma once
#include <sstream>
#include <sys/socket.h>
#include "main/precomp.h"

class Client {
public:
    Client();

    std::string obuf;
    std::string inbuf;
    std::string nickname;
    std::string prefix;   //not used after registration
    int errcode;
    bool registered;

    
private:
    bool ready_for_flush;
    Client operator=(const Client& lhs);
};

