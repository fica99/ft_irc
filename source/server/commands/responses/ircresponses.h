#pragma once

#include "utils/enumstring.h"

namespace ircserv
{

enum Enum_IRCResponses
{
    Enum_IRCResponses_Unknown = 0,
    Enum_IRCResponses_RPL_AWAY = 301,
    Enum_IRCResponses_RPL_LISTSTART = 321,
    Enum_IRCResponses_RPL_LIST = 322,
    Enum_IRCResponses_RPL_LISTEND = 323,
    Enum_IRCResponses_RPL_TOPIC = 332,
    Enum_IRCResponses_RPL_NAMREPLY = 353,
    Enum_IRCResponses_RPL_ENDOFNAMES = 366,
    Enum_IRCResponses_RPL_YOUREOPER = 381,
    Enum_IRCResponses_ERR_NOSUCHNICK = 401,
    Enum_IRCResponses_ERR_NOSUCHSERVER = 402,
    Enum_IRCResponses_ERR_NOSUCHCHANNEL = 403,
    Enum_IRCResponses_ERR_CANNOTSENDTOCHAN = 404,
    Enum_IRCResponses_ERR_TOOMANYCHANNELS = 405,
    Enum_IRCResponses_ERR_TOOMANYTARGETS = 407,
    Enum_IRCResponses_ERR_NORECIPIENT = 411,
    Enum_IRCResponses_ERR_NOTEXTTOSEND = 412,
    Enum_IRCResponses_ERR_NOTOPLEVEL = 413,
    Enum_IRCResponses_ERR_WILDTOPLEVEL = 414,
    Enum_IRCResponses_ERR_NONICKNAMEGIVEN = 431,
    Enum_IRCResponses_ERR_ERRONEUSNICKNAME = 432,
    Enum_IRCResponses_ERR_NICKNAMEINUSE = 433,
    Enum_IRCResponses_ERR_NICKCOLLISION = 436,
    Enum_IRCResponses_ERR_NOTONCHANNEL = 442,
    Enum_IRCResponses_ERR_NEEDMOREPARAMS = 461,
    Enum_IRCResponses_ERR_ALREADYREGISTRED = 462,
    Enum_IRCResponses_ERR_PASSWDMISMATCH = 464,
    Enum_IRCResponses_ERR_CHANNELISFULL = 471,
    Enum_IRCResponses_ERR_INVITEONLYCHAN = 473,
    Enum_IRCResponses_ERR_BANNEDFROMCHAN = 474,
    Enum_IRCResponses_ERR_BADCHANNELKEY = 475,
    Enum_IRCResponses_ERR_BADCHANMASK = 476,
    Enum_IRCResponses_ERR_NOPRIVILEGES = 481,
    Enum_IRCResponses_ERR_CHANOPRIVSNEEDED = 482,
    Enum_IRCResponses_ERR_CANTKILLSERVER = 483,
    Enum_IRCResponses_ERR_NOOPERHOST = 491
};

Begin_Enum_String(Enum_IRCResponses)
{
    Enum_String(Enum_IRCResponses_RPL_AWAY, "301");
    Enum_String(Enum_IRCResponses_RPL_LISTSTART, "321");
    Enum_String(Enum_IRCResponses_RPL_LIST, "322");
    Enum_String(Enum_IRCResponses_RPL_LISTEND, "323");
    Enum_String(Enum_IRCResponses_RPL_TOPIC, "332");
    Enum_String(Enum_IRCResponses_RPL_NAMREPLY, "353");
    Enum_String(Enum_IRCResponses_RPL_ENDOFNAMES, "366");
    Enum_String(Enum_IRCResponses_RPL_YOUREOPER, "381");
    Enum_String(Enum_IRCResponses_ERR_NOSUCHNICK, "401");
    Enum_String(Enum_IRCResponses_ERR_NOSUCHSERVER, "402");
    Enum_String(Enum_IRCResponses_ERR_NOSUCHCHANNEL, "403");
    Enum_String(Enum_IRCResponses_ERR_CANNOTSENDTOCHAN, "404");
    Enum_String(Enum_IRCResponses_ERR_TOOMANYCHANNELS, "405");
    Enum_String(Enum_IRCResponses_ERR_TOOMANYTARGETS, "407");
    Enum_String(Enum_IRCResponses_ERR_NORECIPIENT, "411");
    Enum_String(Enum_IRCResponses_ERR_NOTEXTTOSEND, "412");
    Enum_String(Enum_IRCResponses_ERR_NOTOPLEVEL, "413");
    Enum_String(Enum_IRCResponses_ERR_WILDTOPLEVEL, "414");
    Enum_String(Enum_IRCResponses_ERR_NONICKNAMEGIVEN, "431");
    Enum_String(Enum_IRCResponses_ERR_ERRONEUSNICKNAME, "432");
    Enum_String(Enum_IRCResponses_ERR_NICKNAMEINUSE, "433");
    Enum_String(Enum_IRCResponses_ERR_NICKCOLLISION, "436");
    Enum_String(Enum_IRCResponses_ERR_NOTONCHANNEL, "442");
    Enum_String(Enum_IRCResponses_ERR_NEEDMOREPARAMS, "461");
    Enum_String(Enum_IRCResponses_ERR_ALREADYREGISTRED, "462");
    Enum_String(Enum_IRCResponses_ERR_PASSWDMISMATCH, "464");
    Enum_String(Enum_IRCResponses_ERR_CHANNELISFULL, "471");
    Enum_String(Enum_IRCResponses_ERR_INVITEONLYCHAN, "473");
    Enum_String(Enum_IRCResponses_ERR_BANNEDFROMCHAN, "474");
    Enum_String(Enum_IRCResponses_ERR_BADCHANNELKEY, "475");
    Enum_String(Enum_IRCResponses_ERR_BADCHANMASK, "476");
    Enum_String(Enum_IRCResponses_ERR_NOPRIVILEGES, "481");
    Enum_String(Enum_IRCResponses_ERR_CHANOPRIVSNEEDED, "482");
    Enum_String(Enum_IRCResponses_ERR_CANTKILLSERVER, "483");
    Enum_String(Enum_IRCResponses_ERR_NOOPERHOST, "491");
}
End_Enum_String;

}
