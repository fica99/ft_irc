#pragma once

#include <vector>
#include <map>
#include <string>
#include <poll.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "server/ircclient.h"
#include "server/commands/manager/irccommandsmanager.h"

namespace ircserv
{


class IRCServer
{
public:
    IRCServer(uint16_t port);
    virtual ~IRCServer();
private:
    void Initialize(void);
    void Shutdown(void);
public:
    void acceptConn();
    void recvFromClient();

public:
    bool setNickname(const std::string &nickname);
    bool setPrefix(const std::string &prefix);
    void sendMessage(const std::string &mes, int fd) const;

private:
    int	sendError(int fd, int err, const std::vector<std::string> args);
    int	sendReply(int fd, int rpl, const std::vector<std::string> &args);

private:
    struct sockaddr_in m_Servaddr;
    int m_Fd;
    std::vector<struct pollfd> m_Userpfd;
    std::map<int, IRCClient> m_Clients;
    IRCClient *m_Curr;
    IRCCommandsManager m_CommandsManager;
};

}
