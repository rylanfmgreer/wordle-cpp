/**
 * @file utils.hpp
 * @brief Utility functions for character and number conversions
 * @author Rylan Greer
 */

#ifndef _utils_wordle_hpp
#define _utils_wordle_hpp
#include "../datatypes.hpp"
#include <string>
namespace Wordle
{
    /**
     * @brief Convert a lowercase letter to its numeric representation
     * @param c Character ('a'-'z')
     * @return Numeric value (0-25 where 'a'=0, 'b'=1, etc.)
     */
    inline Letter charToInt(char c) {return c - 'a'; } // 'a' == 97, set 'a' to 0
    
    /**
     * @brief Convert a string to lowercase
     * @param str Input string
     * @return Lowercase version of the string
    */
    
    std::string toLowerCase(const std::string& str);
    /**
     * @brief Convert a digit character to its numeric value
     * @param c Character ('0'-'9')
     * @return Numeric value (0-9)
     */
    inline std::size_t intCharToNum (char c) { return static_cast<std::size_t>(c - '0');  } // '0' == 48, set '0' to 0

    /**
     * @brief Count the number of distinct vowels in a word
     * @param word Input word
     * @return Number of distinct vowels (a, e, i, o, u) in the word
     */
    int countDistinctVowels(const std::string& word);

    /**
     * @brief Check if a word has any double letters
     * @param word Input word
     * @return true if the word contains any letter more than once
     */
    bool hasDoubleLetters(const std::string& word);
}

#endif