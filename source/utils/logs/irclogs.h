#pragma once

#ifdef IRC_LOGGER_DEFINED
#include <plog/Log.h>
#else
#include <cstdio>
#include <string>
#endif // !IRC_LOGGER_DEFINED

#ifdef IRC_LOGGER_DEFINED

#define IRC_LOGE(format, ...) PLOGE.printf(format, __VA_ARGS__)
#define IRC_LOGI(format, ...) PLOGI.printf(format, __VA_ARGS__)
#define IRC_LOGD(format, ...) PLOGD.printf(format, __VA_ARGS__)

#else

#define IRC_LOGE(format, ...) fprintf(stderr, (std::string(format) + "\n").c_str(), __VA_ARGS__)
#define IRC_LOGI(format, ...) fprintf(stdout, (std::string(format) + "\n").c_str(), __VA_ARGS__)
#define IRC_LOGD(format, ...) 

#endif // !IRC_LOGGER_DEFINED
