#pragma once
#include "main/precomp.h"
#include "Client.h"

#include <stdint.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string>
#include <vector>
#include <sstream>
#include <poll.h>
#include <stdio.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include "list"
#define MAX_CONNECTIONS 1024

class Server {
private:
    int fd;
    //struct pollfd *_pfd;
    struct sockaddr_in *servaddr;

    //bool has_eol(const std::ostringstream& buf) const;
    std::vector<struct pollfd> userpfd;
public:
    int _count;
    std::vector<Client *> incoming_connections;
    void recv_from_client();
    explicit Server(uint16_t port);
    //void Slisten();
    void accept_conn();
    void sendMessage() const;
    void handle_inputs();
};

