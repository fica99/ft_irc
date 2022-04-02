#pragma once

#include <string>

namespace ircserv
{

struct CommandLineOptions
{
    unsigned short int  m_Port;
    std::string         m_Password;
};

}
