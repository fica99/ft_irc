#pragma once

#include "utils/enumstring.h"

namespace ircserv
{

enum Enum_IRCCResponses
{
    Enum_IRCResponses_Unknown = 0,
    Enum_IRCResponses_RPL_WELCOME = 1,
};

Begin_Enum_String(Enum_IRCCResponses)
{
    Enum_String(Enum_IRCResponses_RPL_WELCOME, "001");
}
End_Enum_String;

}
