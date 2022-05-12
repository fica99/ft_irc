#pragma once

#include <stdint.h>
#include <cstdlib>
#include <string>
#include <limits>
#include <vector>
#include <utility>
#include <iostream>
#include <exception>
#include <cassert>
#include <sstream>
#include <map>
#include <cstring>

#if defined(IRC_RELEASE) || defined(IRC_DEBUG)

#include <plog/Log.h>
#include <plog/Init.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <plog/Formatters/CsvFormatter.h>
#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>

    #define IRC_LOGGER_INITIALIZED
    #define IRC_PLOGD PLOGD
    #define IRC_PLOGI PLOGI

#else

struct NullStream: public std::stringstream {
   NullStream(): std::stringstream() {}
};

template<typename T>
void operator<<(const NullStream& ss, const T& t) {}

static NullStream nullStream;
static std::ostream &nullostream = nullStream;

    #define IRC_PLOGD nullostream
    #define IRC_PLOGI nullostream

#endif // !(defined(IRC_RELEASE) || defined(IRC_DEBUG))
