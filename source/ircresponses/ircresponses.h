#pragma once

#include "utils/enumstring.h"

namespace ircserv
{

enum Enum_IRCCResponses
{
    Enum_IRCResponses_Unknown = 0,
    Enum_IRCResponses_ERR_NONICKNAMEGIVEN = 431,
    Enum_IRCResponses_ERR_ERRONEUSNICKNAME = 432,
    Enum_IRCResponses_ERR_NICKNAMEINUSE = 433,
    Enum_IRCResponses_ERR_NICKCOLLISION = 436,
    Enum_IRCResponses_ERR_NEEDMOREPARAMS = 461,
    Enum_IRCResponses_ERR_ALREADYREGISTRED = 462
};

Begin_Enum_String(Enum_IRCCResponses)
{
    Enum_String(Enum_IRCResponses_ERR_NONICKNAMEGIVEN, "431");
    Enum_String(Enum_IRCResponses_ERR_ERRONEUSNICKNAME, "432");
    Enum_String(Enum_IRCResponses_ERR_NICKNAMEINUSE, "433");
    Enum_String(Enum_IRCResponses_ERR_NICKCOLLISION, "436");
    Enum_String(Enum_IRCResponses_ERR_NEEDMOREPARAMS, "461");
    Enum_String(Enum_IRCResponses_ERR_ALREADYREGISTRED, "462");
}
End_Enum_String;

}
