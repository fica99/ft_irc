#include "utils/logs/irclogsinitializer.h"

#ifdef IRC_LOGGER_DEFINED
#include <plog/Init.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <plog/Formatters/CsvFormatter.h>
#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#endif // IRC_LOGGER_DEFINED

namespace ircserv
{

IMPLEMENT_SIMPLE_SINGLETON(IRCLogsInitializer);

IRCLogsInitializer::IRCLogsInitializer()
{
    IMPLEMENT_SIMPLE_SINGLETON_CONSTRUCTOR();

    Initialize();
}

void IRCLogsInitializer::Initialize(void)
{
#ifdef IRC_LOGGER_DEFINED
    static plog::RollingFileAppender<plog::CsvFormatter> fileAppender("logs.csv", 1048576, 3);
    static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
#if defined(IRC_DEBUG)
    plog::init(plog::debug, &fileAppender).addAppender(&consoleAppender);
#elif defined(IRC_RELEASE)
    plog::init(plog::info, &fileAppender).addAppender(&consoleAppender);
#endif
#endif // IRC_LOGGER_DEFINED
}

IRCLogsInitializer::~IRCLogsInitializer()
{
    Shutdown();

    IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR();
}

void IRCLogsInitializer::Shutdown(void)
{
}
}
