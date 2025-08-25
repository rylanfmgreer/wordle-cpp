#ifndef _utils_wordle_hpp
#define _utils_wordle_hpp
#include "../datatypes.hpp"

namespace Wordle
{
    inline SmallInt char_to_int(char c) {return c - 'a'; } // 'a' == 97, set 'a' to 0
}

#endif