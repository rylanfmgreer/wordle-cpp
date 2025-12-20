/**
 * @file filter.hpp
 * @brief Word filtering based on Wordle game feedback
 * @author Rylan Greer
 */

#ifndef _WORDLE_WORD_FILTER_HPP___
#define _WORDLE_WORD_FILTER_HPP___

#include "word.hpp"
#include "../datatypes.hpp"
#include <vector>
#include <string>

namespace Wordle
{
    /**
     * @struct LetterPos
     * @brief Represents a letter at a specific position in a word
     */
    struct LetterPos
    {
        std::size_t position;  ///< Position in the word (0-indexed)
        Letter letter;         ///< Letter as numeric value (0-25)
    };

    /**
     * @class WordFilter
     * @brief Filters words based on Wordle game clues (green/yellow/grey letters)
     * 
     * Maintains lists of letters that are:
     * - Green: correct letter in correct position
     * - Yellow: correct letter in wrong position
     * - Grey: letter not in the word (or no more instances)
     */
    class WordFilter
    {

        public:
        /**
         * @brief Filter a word list to only valid words
         * @param word_list The list of words to filter
         * @return Filtered list containing only valid words
         */
        std::vector<Word> filterWordList(const std::vector<Word>& word_list) const;
        
        /**
         * @brief Check if a single word is valid given the current constraints
         * @param word The word to validate
         * @return true if the word satisfies all constraints
         */
        bool isWordValid(const Word& word) const;
        
        /**
         * @brief Add a green (correct position) letter constraint
         * @param position Position in word (0-indexed)
         * @param letter Letter at that position (0-25)
         */
        inline void addGreenLetter(std::size_t position, Letter letter){m_greenLetters.push_back({position, letter});}
        
        /**
         * @brief Add a yellow (wrong position) letter constraint
         * @param position Position where letter was guessed (0-indexed)
         * @param letter Letter that exists elsewhere (0-25)
         */
        inline void addYellowLetter(std::size_t position, Letter letter){m_yellowLetters.push_back({position, letter});}
        
        /**
         * @brief Add a grey (not in word) letter constraint
         * @param position Position where letter was guessed (0-indexed)
         * @param letter Letter not in word (0-25)
         */
        inline void addGreyLetter(std::size_t position, Letter letter){m_greyLetters.push_back({position, letter});}

        /**
         * @brief Parse a positions file and populate the filter
         * @param filename Path to file with format:
         * 
         * green:
         * L1 E2 T3
         * 
         * yellow:
         * A4
         * 
         * grey:
         * R1 S2
         */
        void parsePositionsFile(const std::string& filename);        private:
        std::vector<LetterPos> m_greyLetters;    ///< Letters not in word or exhausted
        std::vector<LetterPos> m_greenLetters;   ///< Letters in correct positions
        std::vector<LetterPos> m_yellowLetters;  ///< Letters in wrong positions
        
        /**
         * @brief Parse a single token like "L1" into LetterPos
         * @param token String containing letter and position
         * @return Parsed LetterPos structure
         */
        LetterPos parseSinglePositionString(std::string& token) const;
        
        /**
         * @brief Check if word satisfies green letter constraints
         * @param word Word to check
         * @return true if all green letters match
         */
        bool checkGreenLetters(const Word& word) const;
        
        /**
         * @brief Check if word satisfies yellow letter constraints
         * @param word Word to check
         * @return true if yellow letters exist in different positions
         */
        bool checkYellowLetters(const Word& word) const;
        
        /**
         * @brief Check if word satisfies grey letter constraints
         * @param word Word to check
         * @return true if grey letters are handled correctly
         */
        bool checkGreyLetters(const Word& word) const;
        
        /**
         * @brief Get minimum possible count of a letter based on constraints
         * @param letter Letter to check (0-25)
         * @return Minimum occurrences this letter must have
         */
        int getMinPossibleCountOfThisLetterInWord(Letter letter) const;
        
        /**
         * @brief Get maximum possible count of a letter based on constraints
         * @param letter Letter to check (0-25)
         * @return Maximum occurrences this letter can have
         */
        int getMaxPossibleCountOfThisLetterInWord(Letter letter) const;

    };

    /**
     * @brief Convenience function to filter word list from file
     * @param positionFilterFilename Path to positions file
     * @param word_list Word list to filter (modified in place)
     */
    void filterOutImpossibleWords(const std::string& positionFilterFilename, std::vector<Word>& word_list);
}
 
#endif