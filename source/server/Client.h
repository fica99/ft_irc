#pragma once
#include "main/precomp.h"

class Client {
public:
    Client();

    std::string obuf;
    std::string inbuf;
    std::string nickname;
    std::string prefix;   //not used after registration
    int fd;
    int errcode;
    bool registered;
};