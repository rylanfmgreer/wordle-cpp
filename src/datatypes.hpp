/**
 * @file datatypes.hpp
 * @brief Core data types and constants for the Wordle solver
 * @author Rylan Greer
 */

#ifndef _datatypes_wordle_hpp
#define _datatypes_wordle_hpp

namespace Wordle
{
    /** @brief Type representing a letter as a numeric value (0-25 for A-Z) */
    typedef short int Letter;
    
    /** @brief Type for large integer values used in calculations */
    typedef int LongInt;
    
    /** @brief Number of letters in the English alphabet */
    const short int ALPHABET_SIZE = 26;
    
    /** @brief Standard Wordle word length */
    const short int WORD_LENGTH = 5;

    /** @brief The first lowercase letter of the English alphabet */
    const Letter FIRST_LETTER_OF_ALPHABET = 'a';
}

#endif // _datatypes_wordle_hpp