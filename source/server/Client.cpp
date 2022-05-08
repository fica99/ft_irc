#include "Client.h"
#include <string.h>

//Client::Client() {}

Client Client::operator=(const Client& lhs) {
    Client cl;

    cl.obuf = lhs.obuf;
    cl.nickname = lhs.nickname;
    cl.ready_for_flush = lhs.ready_for_flush;
    cl.inbuf = lhs.inbuf;
    return cl;
}
