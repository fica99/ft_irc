#pragma once

#include "utils/enumstring.h"

namespace ircserv
{

enum Enum_IRCCResponses
{
    Enum_IRCResponses_Unknown = 0,
    Enum_IRCResponses_ERR_NONICKNAMEGIVEN = 431,
    Enum_IRCResponses_ERR_NEEDMOREPARAMS = 461,
};

Begin_Enum_String(Enum_IRCCResponses)
{
    Enum_String(Enum_IRCResponses_ERR_NONICKNAMEGIVEN, "431");
    Enum_String(Enum_IRCResponses_ERR_NEEDMOREPARAMS, "461");
}
End_Enum_String;

}
