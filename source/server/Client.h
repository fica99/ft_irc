#pragma once
#include <sstream>
#include <sys/socket.h>
#include "main/precomp.h"

class Client {
public:
    bool ready_for_flush;
    int id;
    int fd;
    struct sockaddr sockaddr;
    std::ostringstream buf;
};
