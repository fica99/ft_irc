#include "Server.h"
#include <iostream>

#define LISTEN_QUEUE 128
#define RECV_BUF 1024

Server::Server(uint16_t port): _count(0) {
    //int on = 1;
    servaddr = new struct sockaddr_in;

    memset(servaddr, 0, sizeof(struct sockaddr_in));
    fd = socket(AF_INET, SOCK_STREAM, 0);
    servaddr->sin_family = AF_INET;
    servaddr->sin_addr.s_addr = INADDR_ANY;
    servaddr->sin_port = htons(port);
    //memset(_pfd, 0, sizeof(struct pollfd));

    fcntl(fd, F_SETFL, O_NONBLOCK);
   // if (setsockopt(fd, SOL_SOCKET,  SO_REUSEADDR, (char *)&on, sizeof(on)) == -1)
        //perror("setsockopt");
    socklen_t len = sizeof(struct sockaddr_in);
    if (bind(fd, (struct sockaddr *)servaddr, len) < 0)
        perror("bind");
    listen(fd, LISTEN_QUEUE);
}

void Server::accept_conn() {
    int user_fd;
    static size_t addrlen = sizeof(struct sockaddr_in);

    if ((user_fd = accept(fd, (sockaddr *)servaddr, (socklen_t *)&(addrlen))) > 0){
        struct pollfd pfd;

        pfd.fd = user_fd;
        pfd.events = POLLIN;
        userpfd.push_back(pfd);
    }
}

void Server::recv_from_client() {
    int ready = poll(userpfd.data(), userpfd.size(), 0);
    int i = 0;
    static char buf[RECV_BUF + 1] = {0};

    while (ready--) {
        if (userpfd[i].revents == POLLIN) {
            recv(userpfd[i].fd, buf, RECV_BUF, 0);
            std::cout << buf << std::endl;
            userpfd[i].revents = 0;
        }
        i++;
    }
}

void Server::sendMessage() const {

}
