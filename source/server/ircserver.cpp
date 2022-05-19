#include "main/precomp.h"

#include "server/ircserver.h"

#include <sys/socket.h>
#include <fcntl.h>

#include "server/commands/manager/irccommandsmanager.h"

#define LISTEN_QUEUE 128
#define RECV_BUF 513
#define MAX_CONNECTIONS 1024
#define MAX_CHANNELS 20
#define CHANNEL_DO_NOTHING 0
#define CHANNEL_MAKE_PUBLIC 1
#define CHANNEL_MAKE_PRIVATE 2

typedef std::map<std::string, ircserv::IRCChannel>::iterator IRCChannelIter;
typedef std::map<int, ircserv::IRCClient>::iterator IRCClientIter;
typedef std::pair<IRCChannelIter, bool> IRCChannelPair;

namespace ircserv
{


Enum_IRCResponses IRCServer::joinCommand(const std::string &channel_name) {
    if (m_Channels.size() >= MAX_CHANNELS)
        return Enum_IRCResponses_ERR_TOOMANYCHANNELS;
    IRCChannel tmp(*m_Curr, channel_name);
    IRCChannelPair p = m_Channels.insert(std::make_pair(channel_name, tmp));
    IRCChannel &ch = (*p.first).second;
    if (ch.IsPrivate())
        return Enum_IRCResponses_ERR_INVITEONLYCHAN;

    return ch.add_user(*m_Curr);
}

std::string IRCServer::getTopic(const std::string &channel_name) {
    IRCChannelIter it = m_Channels.find(channel_name);
    return it->second.getTopic();
}

Enum_IRCResponses IRCServer::partCommand(std::string &channel) {
    IRCChannelIter it = m_Channels.find(channel);

    if (it == m_Channels.end())
        return Enum_IRCResponses_ERR_NOSUCHCHANNEL;
    return Enum_IRCResponses_Unknown;
}

Enum_IRCResponses IRCServer::modeCommand(int p, std::string &banned, std::string &channel_name) {
    IRCChannelIter it = m_Channels.find(channel_name);

    if (it == m_Channels.end())
        return Enum_IRCResponses_ERR_NOSUCHCHANNEL;
    IRCChannel &ch = (*it).second;
    if (m_Curr->nickname != ch.get_owner().nickname)
        return Enum_IRCResponses_ERR_CHANOPRIVSNEEDED;
    switch (p)
    {
    case CHANNEL_MAKE_PRIVATE:
        ch.make_private();
        break;
    case CHANNEL_MAKE_PUBLIC:
        ch.make_public();
        break;
    default:
        break;
    }
    if (!banned.empty())
        ch.ban_user(banned);
    return Enum_IRCResponses_RPL_UMODEIS;
}

Enum_IRCResponses IRCServer::topicCommand(std::string &channel_name) {
    return Enum_IRCResponses_RPL_TOPIC;
}

Enum_IRCResponses IRCServer::privmsgCommand(std::string &msg, std::string &receiver)
{
    IRCChannelIter it = m_Channels.find(receiver);
    if (it != m_Channels.end()) {
        if ((*it).second.IsPrivate() && (*it).second.isMember(receiver) == false)
            return Enum_IRCResponses_ERR_CANNOTSENDTOCHAN;
        (*it).second.send_all(msg);
        return Enum_IRCResponses_RPL_AWAY;
    } 
    else {
        for (std::map<int, IRCClient>::iterator it = m_Clients.begin(); it != m_Clients.end(); it = it++) {
            if ((*it).second.nickname == receiver) {
                send((*it).second.fd, msg.c_str(), msg.size(), 0);
                return Enum_IRCResponses_RPL_AWAY;
            }
        }
    }
    return Enum_IRCResponses_ERR_NORECIPIENT;
}

void IRCServer::noticeCommand(std::string &mes, std::string &reciever) {
    privmsgCommand(mes, reciever);
}

IRCServer::IRCServer(uint16_t port)
{
    memset(&m_Servaddr, 0, sizeof(m_Servaddr));
    m_Fd = socket(AF_INET, SOCK_STREAM, 0);
    m_Servaddr.sin_family = AF_INET;
    m_Servaddr.sin_addr.s_addr = INADDR_ANY;
    m_Servaddr.sin_port = htons(port);
    int on = 1;
    fcntl(m_Fd, F_SETFL, O_NONBLOCK);
    setsockopt(m_Fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));
    if (bind(m_Fd, (struct sockaddr *)&m_Servaddr, sizeof(m_Servaddr)) < 0)
    {
        perror("bind");
    }
    listen(m_Fd, LISTEN_QUEUE);

    Initialize();
}

IRCServer::~IRCServer(void)
{
    for (IRCClientIter it = m_Clients.begin(); it != m_Clients.end(); it++) {
        close(it->second.fd);
    }
    close(m_Fd);
    Shutdown();
}

void IRCServer::Initialize(void)
{
}

void IRCServer::Shutdown(void)
{
}

void IRCServer::AcceptConn()
{
    int userFd;
    static size_t addrlen = sizeof(struct sockaddr_in);

    if ((userFd = accept(m_Fd, (sockaddr *)&m_Servaddr, (socklen_t *)&(addrlen))) > 0)
    {
        struct pollfd pfd;
        IRCClient cl;

        fcntl(userFd, F_SETFL, O_NONBLOCK);
        pfd.fd = userFd;
        pfd.events = POLLIN;
        cl.fd = userFd;
        m_Userpfd.push_back(pfd);
        m_Clients.insert(std::make_pair(userFd, cl));
        IRC_LOGI("%s", "new user connected!");
    }
}

void IRCServer::RecvFromClient()
{
    int ready = poll(m_Userpfd.data(), m_Userpfd.size(), 0);
    int i = 0;
    static char buf[RECV_BUF + 1];

    if (ready < 0)
        perror("poll");
    while (ready)
    {
        if (m_Userpfd[i].revents == POLLIN)
        {
            ready--;
            //memset(buf, 0, strlen(buf));
            int rd = recv(m_Userpfd[i].fd, buf, RECV_BUF, 0);
            if (rd == -1) {
                perror("read");
                continue;
            } 
            buf[rd] = 0;
            std::cout << buf;
            if (buf[rd - 1] != '\n')
                std::cout << std::endl;

            if (rd == 0)
            {
                m_Userpfd.erase(m_Userpfd.begin() + i);
                continue;
            }
            else if (rd > 512)
            {
                IRC_LOGD("%s", "recv: message too long");
                continue;
            }
            std::map<int, IRCClient>::iterator cl = m_Clients.find(m_Userpfd[i].fd);
            m_Curr = &((*cl).second);
            m_Curr->inbuf += buf;
            if (strchr(buf, '\n'))
            {
                m_CommandsManager.ProcessCommand(m_Curr->inbuf, this);
                if (m_Curr)
                    m_Curr->inbuf.clear();
            }
            m_Userpfd[i].revents = 0;
        }
        i++;
    }
}

void IRCServer::sendResponse(std::string mes) const
{
    mes += "\n";
    send(m_Curr->fd, mes.c_str(), mes.size(), 0);
}

Enum_IRCResponses IRCServer::setNickname(const std::string &nickname)
{
    for (IRCClientIter it = m_Clients.begin(); it != m_Clients.end(); it++) {
        if (it->second.nickname == nickname) {
            if (!m_Curr->nickname.empty())
                return Enum_IRCResponses_ERR_NICKNAMEINUSE;
            else
                return Enum_IRCResponses_ERR_NICKCOLLISION;
        }
    }
    m_Curr->nickname = nickname;
    return Enum_IRCResponses_Unknown;
}

Enum_IRCResponses IRCServer::userCommand(const std::string &prefix)
{
    for (IRCClientIter it = m_Clients.begin(); it != m_Clients.end(); it++) {
        if (it->second.prefix == prefix)
            return Enum_IRCResponses_ERR_ALREADYREGISTRED;
    }
    m_Curr->prefix = prefix;
    return Enum_IRCResponses_Unknown;
}

void IRCServer::quitCommand() {
    IRCClientIter it = m_Clients.find(m_Curr->fd);
    close(m_Curr->fd);
    for (std::vector<struct pollfd>::iterator it = m_Userpfd.begin(); it != m_Userpfd.end(); it++) {
        if (it->fd == m_Curr->fd) {
            m_Userpfd.erase(it);
            break;
        }
    }
    m_Clients.erase(it);
    m_Curr = NULL;
}

}
