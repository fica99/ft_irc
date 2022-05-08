#pragma once
#include <sstream>
#include <sys/socket.h>
#include "main/precomp.h"

class Client {
public:
    //Client();
    //~Client();
    bool ready_for_flush;
    int id;
    std::string nickname;
    //struct sockaddr sockaddr;
    std::string buf;
    Client operator=(const Client& lhs);
    void setNickname(const std::string &nickname);
};

