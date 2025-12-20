#ifndef _utils_wordle_hpp
#define _utils_wordle_hpp
#include "../datatypes.hpp"

namespace Wordle
{
    inline Letter charToInt(char c) {return c - 'a'; } // 'a' == 97, set 'a' to 0
    inline std::size_t intCharToNum (char c) { return static_cast<std::size_t>(c - '0');  } // '0' == 48, set '0' to 0
}

#endif