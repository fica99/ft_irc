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
#endif // defined(IRC_RELEASE) || defined(IRC_DEBUG)
