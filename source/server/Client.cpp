#include "Client.h"
#include <string.h>

//Client::Client() {}

Client Client::operator=(const Client& lhs) {
    Client cl;

    cl.buf = lhs.buf;
    cl.nickname = lhs.nickname;
    cl.ready_for_flush = lhs.ready_for_flush;
    cl.buf = lhs.buf;
    return cl;
}

void Client::setNickname(const std::string &nickname) {
    this->nickname = nickname;
}