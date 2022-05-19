#pragma once

#include <vector>
#include <map>
#include <string>
#include <poll.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "server/ircclient.h"
#include "server/ircchannel.h"
#include "server/commands/responses/ircresponses.h"
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
    Enum_IRCResponses setNickname(const std::string &nickname);
    Enum_IRCResponses setPrefix(const std::string &prefix);
    void sendMessage(const std::string &mes, int fd) const;
    std::string &get_topic() { return m_Topic; }
    Enum_IRCResponses joinCommand(std::string &channel_name);
    Enum_IRCResponses modeCommand(int p, std::string &banned, std::string &channel_name);
    Enum_IRCResponses partCommand(std::string &channel);
    Enum_IRCResponses topicCommand(std::string &channel_name);
    Enum_IRCResponses privmsgCommand(std::string &msg, std::string &receiver);
    void noticeCommand(std::string &mes, std::string &reciever);

private:
    int	sendError(int fd, int err, const std::vector<std::string> args);
    int	sendReply(int fd, int rpl, const std::vector<std::string> &args);
public:
    IRCClient *m_Curr;

private:
    std::string m_Topic;
    struct sockaddr_in m_Servaddr;
    int m_Fd;
    std::vector<struct pollfd> m_Userpfd;
    std::map<int, IRCClient> m_Clients;
    std::map<std::string, IRCChannel> m_Channels;
    IRCCommandsManager m_CommandsManager;
};

}