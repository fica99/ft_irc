#pragma once
#include <sstream>
#include <sys/socket.h>
#include "main/precomp.h"

class Client {
public:
    std::string obuf;
    std::string inbuf;
    std::string nickname;
    int errcode;
private:
    bool ready_for_flush;
    Client operator=(const Client& lhs);
};

