/**
 * @file word.hpp
 * @brief Word representation and manipulation for Wordle solver
 * @author Rylan Greer
 */

#ifndef _WORDLE_WORD_HPP___
#define _WORDLE_WORD_HPP___

#include <array>
#include <string>
#include "../datatypes.hpp"

namespace Wordle
{
    /**
     * @class Word
     * @brief Represents a Wordle word with efficient letter lookup
     * 
     * Stores a word as both the original string and as numeric arrays
     * for fast letter position and frequency lookups during game solving.
     */
    class Word
    {
        public:
        /**
         * @brief Construct a Word from a string
         * @param word The word string (must be WORD_LENGTH characters)
         */
        Word(const std::string& word);
        
        /**
         * @brief Copy assignment operator
         * @param other The Word to copy from
         * @return Reference to this Word
         */
        Word& operator=(const Word& other);
        
        /**
         * @brief Get the letter at a specific position
         * @param position The position (0-indexed)
         * @return The letter as a numeric value (0-25)
         */
        Letter getLetterAtPosition(std::size_t position) const { return m_letters[position]; }
        
        /**
         * @brief Get the count of a specific letter in the word
         * @param letter The letter to count (0-25 for A-Z)
         * @return Number of times the letter appears
         */
        Letter getLetterCount(Letter letter) const { return m_letterCount[letter]; }

        /**
         * @brief Check if the word contains a specific letter
         * @param letter The letter to check (0-25 for A-Z)
         * @return true if the letter is in the word, false otherwise
         */
        inline bool getWhetherWordContainsLetter(Letter letter) const { return m_letterCount[letter] > 0; }

        /**
         * @brief Get the original word string
         * @return The word as a string
         */
        inline const std::string& getBaseWord() const { return m_baseWord; }

        private:
        const std::string m_baseWord;              ///< The original word string
        Letter m_letters[WORD_LENGTH];              ///< Letters as numeric values by position
        Letter m_letterCount[ALPHABET_SIZE];       ///< Count of each letter in the word
    };
}
#endif // _WORDLE_WORD_HPP___