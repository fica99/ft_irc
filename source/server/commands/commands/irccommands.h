#pragma once

#include "utils/enumstring.h"

namespace ircserv
{

enum Enum_IRCCommands
{
    Enum_IRCCommands_Unknown = 0,
    Enum_IRCCommands_Pass,
    Enum_IRCCommands_Nick,
    Enum_IRCCommands_User,
    Enum_IRCCommands_Oper,
    Enum_IRCCommands_Quit,
    Enum_IRCCommands_Join,
    Enum_IRCCommands_Part,
    Enum_IRCCommands_Names,
    Enum_IRCCommands_List,
    Enum_IRCCommands_Kick,
    Enum_IRCCommands_Privmsg,
    Enum_IRCCommands_Notice,
    Enum_IRCCommands_Kill
};

Begin_Enum_String(Enum_IRCCommands)
{
    Enum_String(Enum_IRCCommands_Pass, "PASS");
    Enum_String(Enum_IRCCommands_Nick, "NICK");
    Enum_String(Enum_IRCCommands_Nick, "USER");
    Enum_String(Enum_IRCCommands_Oper, "OPER");
    Enum_String(Enum_IRCCommands_Quit, "QUIT");
    Enum_String(Enum_IRCCommands_Join, "JOIN");
    Enum_String(Enum_IRCCommands_Part, "PART");
    Enum_String(Enum_IRCCommands_Names, "NAMES");
    Enum_String(Enum_IRCCommands_List, "LIST");
    Enum_String(Enum_IRCCommands_Kick, "KICK");
    Enum_String(Enum_IRCCommands_Privmsg, "PRIVMSG");
    Enum_String(Enum_IRCCommands_Notice, "NOTICE");
    Enum_String(Enum_IRCCommands_Kill, "KILL");
}
End_Enum_String;

}
