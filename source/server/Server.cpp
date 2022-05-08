#include "Server.h"

#include "ircmessages/lexer/irclexer.h"
#include "ircmessages/parser/ircparser.h"
#include <unistd.h>


Server::Server(uint16_t port): _count(0) {
    //int on = 1;
    servaddr = new struct sockaddr_in;

    memset(servaddr, 0, sizeof(struct sockaddr_in));
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    servaddr->sin_family = AF_INET;
    servaddr->sin_addr.s_addr = INADDR_ANY;
    servaddr->sin_port = htons(port);
    //memset(_pfd, 0, sizeof(struct pollfd));

    fcntl(_fd, F_SETFL, O_NONBLOCK);
   // if (setsockopt(fd, SOL_SOCKET,  SO_REUSEADDR, (char *)&on, sizeof(on)) == -1)
        //perror("setsockopt");
    socklen_t len = sizeof(struct sockaddr_in);
    if (bind(_fd, (struct sockaddr *)servaddr, len) < 0)
        perror("bind");
    listen(_fd, LISTEN_QUEUE);
}

void Server::accept_conn() {
    int user_fd;
    static size_t addrlen = sizeof(struct sockaddr_in);

    if ((user_fd = accept(_fd, (sockaddr *)servaddr, (socklen_t *)&(addrlen))) > 0) {
        struct pollfd pfd;
        
        fcntl(user_fd, F_SETFL, O_NONBLOCK);
        Client cl;
        pfd.fd = user_fd;
        pfd.events = POLLIN;
        userpfd.push_back(pfd);

        //clients.insert(std::make_pair(fd, cl));
    }
}

void Server::recv_from_client() {
    int ready = poll(userpfd.data(), userpfd.size(), 0);
    int i = 0;
    static char buf[RECV_BUF + 1];

    if (ready < 0)
        perror("poll");
    while (ready--) {
        if (userpfd[i].revents == POLLIN) {
            int read = recv(userpfd[i].fd, buf, RECV_BUF, 0);
            if (read == 0) {
                userpfd.erase(userpfd.begin() + i);
                continue;
            } else if (read > 512) {
                std::cerr << "recv: message too long" << std::endl;
                continue ;
            }
            ircserv::IRCParser parser;
            ircserv::IRCLexer lex;
            ircserv::IRCCommand *command = parser.CreateCommand(lex.Tokenize(std::string(buf)));
            std::map<int, Client>::iterator cl = clients.find(userpfd[i].fd);
            command->ProcessCommand(this, *cl);
            if (cl == clients.end())
                std::cout << "end!" << std::endl;
            userpfd[i].revents = 0;
            std::string mes(buf);
            //std::cout << "point" << std::endl;
            sendMessage(mes, userpfd[i].fd);
        }
        i++;
    }
}


void Server::sendMessage(const std::string &mes, int fd) const {
    send(fd, mes.c_str(), mes.size(), 0);
}