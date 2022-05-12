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
#define IRC_LOGGER_INITIALIZED
#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"
#endif // defined(IRC_RELEASE) || defined(IRC_DEBUG)
