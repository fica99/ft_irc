#pragma once

#include <string>
#include <vector>

namespace ircserv
{

namespace IRCParsingHelper
{

struct IRCSymbolsDefinition
{
    static const std::string LETTERS_ASCII;
    static const std::string DIGITS_ASCII;
    static const std::string SPECIAL_ASCII;
    static const std::string WHITE_ASCII;
    static const std::string NON_CHSTRING_ASCII;
    static const std::string SPACE_ASCII;
    static const std::string CRLF_ASCII;
};

bool IsSymbolLetter(char symb);
bool IsSymbolDigit(char symb);
bool IsSymbolSpace(char symb);

bool IsUser(const std::string& user);
bool IsNick(const std::string& nick);
bool IsRealname(const std::string& realname);
bool IsChannel(const std::string& channel);
bool IsChannels(const std::string& channelsStr);

bool IsCommand(const std::string& command);
bool IsNumeriousCommand(const std::string& command);
bool IsLetterCommand(const std::string& command);

std::vector<std::string> Split(std::string line, const std::string& delim);

}

}
