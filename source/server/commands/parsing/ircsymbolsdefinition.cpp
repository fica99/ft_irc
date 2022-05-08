#include "main/precomp.h"

#include "server/commands/parsing/ircsymbolsdefinition.h"

namespace ircserv
{

const std::string IRCSymbolsDefinition::LETTERS_ASCII = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const std::string IRCSymbolsDefinition::DIGITS_ASCII = "0123456789";
const std::string IRCSymbolsDefinition::SPECIAL_ASCII = "-[]\\`/^{}";
const std::string IRCSymbolsDefinition::WHITE_ASCII = " \0\r\n";
const std::string IRCSymbolsDefinition::NON_CHSTRING_ASCII = " \a\0\r\n,";

}
