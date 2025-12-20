/**
 * @file utils.hpp
 * @brief Utility functions for character and number conversions
 * @author Rylan Greer
 */

#ifndef _utils_wordle_hpp
#define _utils_wordle_hpp
#include "../datatypes.hpp"

namespace Wordle
{
    /**
     * @brief Convert a lowercase letter to its numeric representation
     * @param c Character ('a'-'z')
     * @return Numeric value (0-25 where 'a'=0, 'b'=1, etc.)
     */
    inline Letter charToInt(char c) {return c - 'a'; } // 'a' == 97, set 'a' to 0
    
    /**
     * @brief Convert a digit character to its numeric value
     * @param c Character ('0'-'9')
     * @return Numeric value (0-9)
     */
    inline std::size_t intCharToNum (char c) { return static_cast<std::size_t>(c - '0');  } // '0' == 48, set '0' to 0
}

#endif