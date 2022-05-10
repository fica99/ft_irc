#include "main/precomp.h"

#include "server/commands/parsing/ircparsinghelper.h"

namespace ircserv
{

const std::string IRCParsingHelper::IRCSymbolsDefinition::LETTERS_ASCII = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const std::string IRCParsingHelper::IRCSymbolsDefinition::DIGITS_ASCII = "0123456789";
const std::string IRCParsingHelper::IRCSymbolsDefinition::SPECIAL_ASCII = "-[]\\`/^{}";
const std::string IRCParsingHelper::IRCSymbolsDefinition::WHITE_ASCII = " \0\r\n";
const std::string IRCParsingHelper::IRCSymbolsDefinition::NON_CHSTRING_ASCII = " \a\0\r\n,";
const std::string IRCParsingHelper::IRCSymbolsDefinition::SPACE_ASCII = " ";
const std::string IRCParsingHelper::IRCSymbolsDefinition::CRLF_ASCII = "\r\n";

bool IRCParsingHelper::IsSymbolLetter(char symb)
{
    return IRCSymbolsDefinition::LETTERS_ASCII.find(symb) != IRCSymbolsDefinition::LETTERS_ASCII.npos;
}

bool IRCParsingHelper::IsSymbolDigit(char symb)
{
    return IRCSymbolsDefinition::DIGITS_ASCII.find(symb) != IRCSymbolsDefinition::DIGITS_ASCII.npos;
}

bool IRCParsingHelper::IsSymbolSpace(char symb)
{
    return IRCSymbolsDefinition::SPACE_ASCII.find(symb) != IRCSymbolsDefinition::SPACE_ASCII.npos;
}

bool IRCParsingHelper::IsUser(const std::string& user)
{
    size_t pos;

    if (user.empty())
    {
        return false;
    }
    pos = user.find_first_of(IRCSymbolsDefinition::WHITE_ASCII);
    return pos == user.npos;
}

bool IRCParsingHelper::IsNick(const std::string& nick)
{
    size_t pos;

    if (nick.empty() || nick.size() > 9 || !IsSymbolLetter(nick[0]))
    {
        return false;
    }
    pos = nick.find_first_not_of(IRCSymbolsDefinition::LETTERS_ASCII + IRCSymbolsDefinition::DIGITS_ASCII + IRCSymbolsDefinition::SPECIAL_ASCII);
    return pos == nick.npos;
}

bool IRCParsingHelper::IsRealname(const std::string& realname)
{
    size_t pos;

    if (realname.empty())
    {
        return false;
    }
    pos = realname.find_first_of(IRCSymbolsDefinition::SPACE_ASCII);
    return pos != realname.npos;
}

bool IRCParsingHelper::IsChannel(const std::string& channel)
{
    size_t pos = 0;

    if (channel.empty() || channel.size() > 200)
    {
        return false;
    }
    if (channel[0] != '&' && channel[0] != '#')
    {
        return false;
    }
    pos = channel.find_first_of(IRCSymbolsDefinition::NON_CHSTRING_ASCII);
    return pos == channel.npos;
}

bool IRCParsingHelper::IsChannels(const std::string& channelsStr)
{
    std::vector<std::string> channelsVec;

    if (channelsStr.empty())
    {
        return false;
    }
    channelsVec = Split(channelsStr, ",");
    for (size_t i = 0; i < channelsVec.size(); ++i)
    {
        if (!IsChannel(channelsVec[i]))
        {
            return false;
        }
    }
    return true;
}


bool IRCParsingHelper::IsCommand(const std::string& command)
{
    return IsLetterCommand(command) || IsNumeriousCommand(command);
}

bool IRCParsingHelper::IsNumeriousCommand(const std::string& command)
{
    size_t pos;

    if (command.size() != 3)
    {
        return false;
    }
    pos = command.find_first_not_of(IRCSymbolsDefinition::DIGITS_ASCII);
    return pos == command.npos;
}

bool IRCParsingHelper::IsLetterCommand(const std::string& command)
{
    size_t pos;

    if (command.empty())
    {
        return false;
    }
    pos = command.find_first_not_of(IRCSymbolsDefinition::LETTERS_ASCII);
    return pos == command.npos;
}

std::vector<std::string> IRCParsingHelper::Split(std::string line, const std::string& delim)
{
    std::vector<std::string> parts;
    size_t pos = 0;

    while ((pos = line.find(delim)) != line.npos)
    {
        parts.push_back(line.substr(0, pos));
        line.erase(0, pos + delim.size());
    }
    parts.push_back(line);
    return parts;
}

}
