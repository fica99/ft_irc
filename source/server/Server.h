#pragma once
#include "main/precomp.h"
#include <poll.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <fcntl.h>
#include "server/Client.h"
#include "server/commands/commands/answers.h"
#define MAX_CONNECTIONS 1024
#define LISTEN_QUEUE 128
#define RECV_BUF 513

class Server {
public:
    explicit Server(uint16_t port);
private:
    int m_fd;
    struct sockaddr_in *m_servaddr;
    std::vector<struct pollfd> m_userpfd;
    std::map<int, Client> m_clients;
    Client *m_curr;
    std::set<std::string> nickname_list;

    int	sendError(int fd, int err, const std::vector<std::string> args);
    int	sendReply(int fd, int rpl, const std::vector<std::string> &args);
public:
    void recv_from_client();
    void accept_conn();
    bool setNickname(std::string &nickname);
    bool setPrefix(std::string &prefix);
    void sendMessage(const std::string &mes, int fd) const;
    bool reg_nickname(std::string &nick);
    bool find_nickname(std::string &nick);
    bool delete_nickname(std::string &nickname);
};

