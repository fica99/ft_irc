#pragma once

#include "utils/enumstring.h"

namespace ircserv
{

enum Enum_IRCCommands
{
    Enum_IRCCommands_Unknown = 0,
    Enum_IRCCommands_Pass,
    Enum_IRCCommands_Nick,
    // add commands here
};

Begin_Enum_String(Enum_IRCCommands)
{
    Enum_String(Enum_IRCCommands_Pass, "PASS");
    Enum_String(Enum_IRCCommands_Nick, "NICK");
    // add commands here
}
End_Enum_String;

}
