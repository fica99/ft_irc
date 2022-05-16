#include "Server.h"

#include "server/commands/parsing/lexer/irclexer.h"
#include "server/commands/parsing/parser/ircparser.h"
#include "server/commands/manager/irccommandsmanager.h"
#include <stdio.h>
#include <unistd.h>


Channel::Channel(Client &creator): fprivate(false), owner(creator) {}

// void Channel::add_op(Client &cl) {
// 	//todo if { check_pass(); sendError(); }
// 	this->ops.push_back(cl);
// }

// void Channel::add_user(Client &cl) {
// 	users.push_back(cl);
// }

Server::Server(uint16_t port) {
    m_servaddr = new struct sockaddr_in;

    memset(m_servaddr, 0, sizeof(struct sockaddr_in));
    m_fd = socket(AF_INET, SOCK_STREAM, 0);
    m_servaddr->sin_family = AF_INET;
    m_servaddr->sin_addr.s_addr = INADDR_ANY;
    m_servaddr->sin_port = htons(port);

    fcntl(m_fd, F_SETFL, O_NONBLOCK);
    socklen_t len = sizeof(struct sockaddr_in);
    if (bind(m_fd, (struct sockaddr *)m_servaddr, len) < 0)
        perror("bind");
    listen(m_fd, LISTEN_QUEUE);
}

void Server::accept_conn() {
    int user_fd;
    static size_t addrlen = sizeof(struct sockaddr_in);

    if ((user_fd = accept(m_fd, (sockaddr *)m_servaddr, (socklen_t *)&(addrlen))) > 0) {
        struct pollfd pfd;
        Client cl;

        fcntl(user_fd, F_SETFL, O_NONBLOCK);
        pfd.fd = user_fd;
        pfd.events = POLLIN;
        m_userpfd.push_back(pfd);
		cl.fd = user_fd;
        m_clients.insert(std::make_pair(user_fd, cl));
    }
}

void Server::recv_from_client() {
    int ready = poll(m_userpfd.data(), m_userpfd.size(), 0);
    int i = 0;
    static char buf[RECV_BUF + 1];
    
    if (ready < 0)
        perror("poll");
    while (ready--) {
        if (m_userpfd[i].revents == POLLIN) {
            int read = recv(m_userpfd[i].fd, buf, RECV_BUF, 0);

            buf[read] = 0;
            std::cout << buf;
            if (buf[read - 1] != '\n')
            std::cout << std::endl;

            if (read == 0) {
                m_userpfd.erase(m_userpfd.begin() + i);
                continue;
            } else if (read > 512) {
                std::cerr << "recv: message too long" << std::endl;
                continue ;
            }
            std::map<int, Client>::iterator cl = m_clients.find(m_userpfd[i].fd);
            m_curr = &((*cl).second);
            if (!m_curr->prefix.empty() || m_curr->nickname.empty()) {
                std::vector<std::string> v(0);
                sendError(m_userpfd[i].fd, ERR_NOTREGISTERED, v);
            }
            m_curr->inbuf += buf;
            if (strchr(buf, '\n')) {
				ircserv::IRCCommandsManager manager;
				manager.ProcessCommand(m_curr->inbuf, this);
			}
            m_userpfd[i].revents = 0;
        }
        i++;
    }
}

bool Server::find_nickname(std::string &nick) {
	if (nickname_list.find(nick) != nickname_list.end())
		return true;
	return false;
}

bool Server::reg_nickname(std::string &nick) {
	std::pair<std::set<std::string>::iterator, bool> ret = nickname_list.insert(nick);

	return ret.second;
}

bool Server::delete_nickname(std::string &nick) {
	size_t ret = nickname_list.erase(nick);

	return ret;
}

void Server::sendMessage(const std::string &mes, int fd) const {
    send(fd, mes.c_str(), mes.size(), 0);
}

bool Server::setNickname(std::string &nickname) {
	if (m_curr->nickname.empty())
    	m_curr->nickname = nickname;
    return true;
}

bool Server::setPrefix(std::string &prefix) {
	if (m_curr->prefix.empty())
    	m_curr->prefix = prefix;
    return true;
}

// bool Server::join_channel(std::string &channel_name, Client &cl)
// {
// 	Channel ch(cl);


// 	pair<map<string, Channel>::iterator, bool> p = m_channels_list.insert(std::make_pair(channel_name, ch));
// 	if (p.second == false) {
// 		(*p.first).second.
// 	}
// }


int		Server::sendReply(int fd, int rpl, const std::vector<std::string> &args)
{
	std::string	msg = ":ft_irc ";
	std::stringstream	ss;
	ss << rpl;
	msg += ss.str() + " " + m_curr->nickname + " ";
	switch (rpl)
	{
	case RPL_USERHOST:
		msg += ":" + args[0] + "\n";
		break;
	case RPL_ISON:
		msg += ":" + args[0] + "\n";
		break;
	case RPL_AWAY:
		msg += args[0] + " :" + args[1] + "\n";
		break;
	case RPL_UNAWAY:
		msg += ":You are no longer marked as being away\n";
		break;
	case RPL_NOWAWAY:
		msg += ":You have been marked as being away\n";
		break;
	case RPL_WHOISUSER:
		msg += args[0] + " " + args[1] + " " + args[2] + " * :" + args[3] + "\n";
		break;
	case RPL_WHOISSERVER:
		msg += args[0] + " " + args[1] + " :" + args[2] + "\n";
		break;
	case RPL_WHOISOPERATOR:
		msg += args[0] + " :is an IRC operator\n";
		break;
	case RPL_WHOISIDLE:
		msg += args[0] + " " + args[1] + " " + args[2] + " :seconds idle\n";
		break;
	case RPL_ENDOFWHOIS:
		msg += args[0] + " :End of /WHOIS list\n";
		break;
	case RPL_WHOISCHANNELS:
		msg += args[0] + " :" + args[1] + "\n";
		break;
	case RPL_WHOWASUSER:
		msg += args[0] + " " + args[1] + " " + args[2] + " * :" + args[3] + "\n";
		break;
	case RPL_ENDOFWHOWAS:
		msg += args[0] + " :End of WHOWAS\n";
		break;
	case RPL_LISTSTART:
		msg += "Channel :Users  Name\n";
		break;
	case RPL_LIST:
		msg += args[0] +  " " + args[1] + " :" + args[2] + "\n";
		break;
	case RPL_LISTEND:
		msg += ":End of /LIST\n";
		break;
	case RPL_CHANNELMODEIS:
		msg += args[0] + " +" + args[1] + "\n";
		break;
	case RPL_NOTOPIC:
		msg += args[0] + " :No topic is set\n";
		break;
	case RPL_TOPIC:
		msg += args[0] + " :" + args[1] + "\n";
		break;
	case RPL_INVITING:
		msg += args[0] + " " + args[1] + "\n";
		break;
	case RPL_SUMMONING:
		msg += args[0] + " :Summoning user to IRC\n";
		break;
	case RPL_VERSION:
		msg += args[0] + "." + args[1] + " " + args[2] + " :" + args[3] + "\n";
		break;
	case RPL_WHOREPLY:
		msg += args[0] + " " + args[1] + " " + args[2] + " " + args[3] + " ";
		msg += args[4] + " " + args[5] + " :" + args[6] + " " + args[7] + "\n";
		break;
	case RPL_ENDOFWHO:
		msg += args[0] + " :End of /WHO list\n";
		break;
	case RPL_NAMREPLY:
		msg += args[0] + " :" + args[1] + "\n";
		break;
	case RPL_ENDOFNAMES:
		msg += args[0] + " :End of /NAMES list\n";
		break;
	case RPL_LINKS:
		msg += args[0] + " " + args[1] + ": " + args[2] + " " + args[3] + "\n";
		break;
	case RPL_ENDOFLINKS:
		msg += args[0] + " :End of /LINKS list\n";
		break;
	case RPL_BANLIST:
		msg += args[0] + " " + args[1] + "\n";
		break;
	case RPL_ENDOFBANLIST:
		msg += args[0] + " :End of channel ban list\n";
		break;
	case RPL_INFO:
		msg += ":" + args[0] + "\n";
		break;
	case RPL_ENDOFINFO:
		msg += ":End of /INFO list\n";
		break;
	case RPL_MOTDSTART:
		msg += ":- " + args[0] + " Message of the day - \n";
		break;
	case RPL_MOTD:
		msg += ":- " + args[0] + "\n";
		break;
	case RPL_ENDOFMOTD:
		msg += ":End of /MOTD command\n";
		break;
	case RPL_YOUREOPER:
		msg += ":You are now an IRC operator\n";
		break;
	case RPL_REHASHING:
		msg += args[0] + " :Rehashing\n";
		break;
	case RPL_TIME:
		msg += args[0] + " :" + args[1]; // ctime return string following '\n'
		break;
	case RPL_USERSSTART:
		msg += ":UserID   Terminal  Host\n";
		break;
	case RPL_USERS:
		msg += ":%-8s %-9s %-8s\n"; // Хз, что это UPD: Понял, строка длиной 8 символов
		break;
	case RPL_ENDOFUSERS:
		msg += ":End of users\n";
		break;
	case RPL_NOUSERS:
		msg += ":Nobody logged in\n";
		break;
	case RPL_TRACELINK:
		msg += "Link " + args[0] + " " + args[1] + " " + args[2] + "\n";
		break;
	case RPL_TRACECONNECTING:
		msg += "Try. " + args[0] + " " + args[1] + "\n";
		break;
	case RPL_TRACEHANDSHAKE:
		msg += "H.S. " + args[0] + " " + args[1] + "\n";
		break;
	case RPL_TRACEUNKNOWN:
		msg += "???? " + args[0] + " " + args[1] + "\n"; // ????
		break;
	case RPL_TRACEOPERATOR:
		msg += "Oper " + args[0] + " " + args[1] + "\n";
		break;
	case RPL_TRACEUSER:
		msg += "User " + args[0] + " " + args[1] + "\n";
		break;
	case RPL_TRACESERVER:
		msg += "Serv " + args[0] + " " + args[1] + "S " + args[2] + "C ";
		msg += args[3] + " " + args[4] + "@" + args[5] + "\n";
		break;
	case RPL_TRACENEWTYPE:
		msg += args[0] + " 0 " + args[1] + "\n";
		break;
	case RPL_TRACELOG:
		msg += "File " + args[0] + " " + args[1] + "\n";
		break;
	case RPL_STATSLINKINFO:
		msg += args[0] + " " + args[1] + " " + args[2] + " " + args[3] + " ";
		msg += args[4] + " " + args[5] + " " + args[6] + "\n";
		break;
	case RPL_STATSCOMMANDS:
		msg += args[0] + " " + args[1] + "\n";
		break;
	case RPL_STATSCLINE:
		msg += "C " + args[0] + " * " + args[1] + " " + args[2] + " " + args[3] + "\n";
		break;
	case RPL_STATSNLINE:
		msg += "N " + args[0] + " * " + args[1] + " " + args[2] + " " + args[3] + "\n";
		break;
	case RPL_STATSILINE:
		msg += "I " + args[0] + " * " + args[1] + " " + args[2] + " " + args[3] + "\n";
		break;
	case RPL_STATSKLINE:
		msg += "K " + args[0] + " * " + args[1] + " " + args[2] + " " + args[3] + "\n";
		break;
	case RPL_STATSYLINE:
		msg += "Y " + args[0] + " * " + args[1] + " " + args[2] + " " + args[3] + "\n";
		break;
	case RPL_ENDOFSTATS:
		msg += args[0] + " :End of /STATS report\n";
		break;
	case RPL_STATSLLINE:
		msg += "L " + args[0] + " * " + args[1] + " " + args[2] + "\n";
		break;
	case RPL_STATSUPTIME:
		msg += ":Server Up %d days %d:%02d:%02d\n"; // Поменять
		break;
	case RPL_STATSOLINE:
		msg += "O " + args[0] + " * " + args[1] + "\n";
		break;
	case RPL_STATSHLINE:
		msg += "H " + args[0] + " * " + args[1] + "\n";
		break;
	case RPL_UMODEIS:
		msg += args[0] + "\n";
		break;
	case RPL_LUSERCLIENT:
		msg += ":There are " + args[0] + " users and " + args[1];
		msg += " invisible on " + args[2] + " servers\n";
		break;
	case RPL_LUSEROP:
		msg += args[0] + " :operator(s) online\n";
		break;
	case RPL_LUSERUNKNOWN:
		msg += args[0] + " :unknown connection(s)\n";
		break;
	case RPL_LUSERCHANNELS:
		msg += args[0] + " :channels formed\n";
		break;
	case RPL_LUSERME:
		msg += ":I have " + args[0] + " clients and " + args[1] + " servers\n";
		break;
	case RPL_ADMINME:
		msg += args[0] + " :Administrative info\n";
		break;
	case RPL_ADMINLOC1:
		msg += ":Name     " + args[0] + "\n";
		break;
	case RPL_ADMINLOC2:
		msg += ":Nickname " + args[0] + "\n";
		break;
	case RPL_ADMINEMAIL:
		msg += ":E-Mail   " + args[0] + "\n";
		break;
	default:
		msg += "UNKNOWN REPLY\n";
		break;
	}
	send(fd, msg.c_str(), msg.size(), 0);
	return 0;
}


int		Server::sendError(int fd, int err, const std::vector<std::string> args)
{
	std::string	msg = ":ft_irc ";
	std::stringstream	ss;
	ss << err;
	msg += ss.str() + " " + m_curr->nickname;
	switch (err)
	{
	case ERR_NOSUCHNICK:
		msg += " " + args[0] + " :No such nick/channel\n";
		break;
	case ERR_NOSUCHSERVER:
		msg += " " + args[0] + " :No such server\n";
		break;
	case ERR_NOSUCHCHANNEL:
		msg += " " + args[0] + " :No such channel\n";
		break;
	case ERR_CANNOTSENDTOCHAN:
		msg += " " + args[0] + " :Cannot send to channel\n";
		break;
	case ERR_TOOMANYCHANNELS:
		msg += " " + args[0] + " :You have joined too many channels\n";
		break;
	case ERR_WASNOSUCHNICK:
		msg += " " + args[0] + " :There was no such nickname\n";
		break;
	case ERR_TOOMANYTARGETS:
		msg += " " + args[0] + " :Duplicate recipients. No args[0] delivered\n";
		break;
	case ERR_NOORIGIN:
		msg += " :No origin specified\n";
		break;
	case ERR_NORECIPIENT:
		msg += " :No recipient given (" + args[0] + ")\n";
		break;
	case ERR_NOTEXTTOSEND:
		msg += " :No text to send\n";
		break;
	case ERR_NOTOPLEVEL:
		msg += " " + args[0] + " :No toplevel domain specified\n";
		break;
	case ERR_WILDTOPLEVEL:
		msg += " " + args[0] + " :Wildcard in toplevel domain\n";
		break;
	case ERR_UNKNOWNCOMMAND:
		msg += " " + args[0] + " :Unknown command\n";
		break;
	case ERR_NOMOTD:
		msg += " :MOTD File is missing\n";
		break;
	case ERR_NOADMININFO:
		msg += " " + args[0] + " :No administrative info available\n";
		break;
	case ERR_FILEERROR:
		msg += " :File error doing \n" + args[0] + " on " + args[1] + "\n";
		break;
	case ERR_NONICKNAMEGIVEN:
		msg += " :No nickname given\n";
		break;
	case ERR_ERRONEUSNICKNAME:
		msg += " " + args[0] + " :Erroneus nickname\n";
		break;
	case ERR_NICKNAMEINUSE:
		msg += " " + args[0] + " :Nickname is already in use\n";
		break;
	case ERR_NICKCOLLISION:
		msg += " " + args[0] + " :Nickname collision KILL\n";
		break;
	case ERR_USERNOTINCHANNEL:
		msg += " " + args[0] + " " + args[1] + " :They aren't on that channel\n";
		break;
	case ERR_NOTONCHANNEL:
		msg += " " + args[0] + " :You're not on that channel\n";
		break;
	case ERR_USERONCHANNEL:
		msg += " " + args[0] + " " + args[1] + " :is already on channel\n";
		break;
	case ERR_NOLOGIN:
		msg += " " + args[0] + " :User not logged in\n";
		break;
	case ERR_SUMMONDISABLED:
		msg += " :SUMMON has been disabled\n";
		break;
	case ERR_USERSDISABLED:
		msg += " :USERS has been disabled\n";
		break;
	case ERR_NOTREGISTERED:
		msg += " :You have not registered\n";
		break;
	case ERR_NEEDMOREPARAMS:
		msg += " " + args[0] + " :Not enough parameters\n";
		break;
	case ERR_ALREADYREGISTRED:
		msg += " :You may not reregister\n";
		break;
	case ERR_NOPERMFORHOST:
		msg += " :Your host isn't among the privileged\n";
		break;
	case ERR_PASSWDMISMATCH:
		msg += " :Password incorrect\n";
		break;
	case ERR_YOUREBANNEDCREEP:
		msg += " :You are banned from this server\n";
		break;
	case ERR_KEYSET:
		msg += " " + args[0] + " :Channel key already set\n";
		break;
	case ERR_CHANNELISFULL:
		msg += " " + args[0] + " :Cannot join channel (+l)\n";
		break;
	case ERR_UNKNOWNMODE:
		msg += " " + args[0] + " :is unknown mode char to me\n";
		break;
	case ERR_INVITEONLYCHAN:
		msg += " " + args[0] + " :Cannot join channel (+i)\n";
		break;
	case ERR_BANNEDFROMCHAN:
		msg += " " + args[0] + " :Cannot join channel (+b)\n";
		break;
	case ERR_BADCHANNELKEY:
		msg += " " + args[0] + " :Cannot join channel (+k)\n";
		break;
	case ERR_NOPRIVILEGES:
		msg += " :Permission Denied- You're not an IRC operator\n";
		break;
	case ERR_CHANOPRIVSNEEDED:
		msg += " " + args[0] + " :You're not channel operator\n";
		break;
	case ERR_CANTKILLSERVER:
		msg += " :You cant kill a server!\n";
		break;
	case ERR_NOOPERHOST:
		msg += " :No O-lines for your host\n";
		break;
	case ERR_UMODEUNKNOWNFLAG:
		msg += " :Unknown MODE flag\n";
		break;
	case ERR_USERSDONTMATCH:
		msg += " :Cant change mode for other users\n";
		break;
	default:
		msg += "UNKNOWN ERROR\n";
		break;
	}
	send(fd, msg.c_str(), msg.size(), 0);
	return (-1);
}