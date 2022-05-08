#pragma once
#include "main/precomp.h"
#include <poll.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <map>

#include <stdio.h>
#include <cstring>
#include <netinet/in.h>
#include <fcntl.h>
#include <iostream>
#include "server/Client.h"
#include "server/commands/commands/answers.h"
#define MAX_CONNECTIONS 1024
#define LISTEN_QUEUE 128
#define RECV_BUF 513

class Server {
public:
    explicit Server(uint16_t port);
private:
    int _fd;
    struct sockaddr_in *servaddr;
    std::vector<struct pollfd> userpfd;
    std::map<int, Client> clients;
    Client *curr;
    int	sendError(int fd, int err, const std::vector<std::string> args);
    int		sendReply(int fd, int rpl, const std::vector<std::string> &args);
public:
    void recv_from_client();
    void accept_conn();
    bool setNickname(std::string &nickname);
    void sendMessage(const std::string &mes, int fd) const;
};

