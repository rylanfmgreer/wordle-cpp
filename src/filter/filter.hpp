/**
 * @file filter.hpp
 * @brief Word filtering based on Wordle game feedback
 * @author Rylan Greer
 */

#ifndef _WORDLE_WORD_FILTER_HPP___
#define _WORDLE_WORD_FILTER_HPP___

#include "../word/word.hpp"
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
        bool operator==(const LetterPos& other) const
        {
            return position == other.position && letter == other.letter;
        }
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
        WordFilter() = default;
        WordFilter(const WordFilter& other) = default;
        WordFilter& operator=(const WordFilter& other) = default;
        ~WordFilter() = default;
        /**
         * @brief Filter a word list to only valid words
         * @param p_wordList The list of words to filter
         * @return Filtered list containing only valid words
         */
        std::vector<Word> filterWordList(const std::vector<Word>& p_wordList) const;
        
        /**
         * @brief Check if a single word is valid given the current constraints
         * @param p_word The p_word to validate
         * @return true if the word satisfies all constraints
         */
        bool isWordValid(const Word& p_word) const;

        /**
         * @brief Update the filter with feedback from a guess
         * @param p_guessedWord The word that was guessed
         * @param p_realWord The actual correct word
         */
        void updateWithGuess(const Word& p_guessedWord, const Word& p_realWord);
        /**
         * @brief Add a green (correct position) letter constraint
         * @param p_position Position in word (0-indexed)
         * @param p_letter Letter at that p_position (0-25)
         */
        inline void addGreenLetter(std::size_t p_position, Letter p_letter){ addLetterIfNotExists(m_greenLetters, {p_position, p_letter});}
        
        /**
         * @brief Add a yellow (wrong position) letter constraint
         * @param p_position Position where letter was guessed (0-indexed)
         * @param p_letter Letter that exists elsewhere (0-25)
         */
        inline void addYellowLetter(std::size_t p_position, Letter p_letter){ addLetterIfNotExists(m_yellowLetters, {p_position, p_letter});}
        
        /**
         * @brief Add a grey (not in word) letter constraint
         * @param p_position Position where letter was guessed (0-indexed)
         * @param p_letter Letter not in p_word (0-25)
         */
        inline void addGreyLetter(std::size_t p_position, Letter p_letter){ addLetterIfNotExists(m_greyLetters, {p_position, p_letter});}

        /**
         * @brief Parse a positions file and populate the filter
         * @param p_filename Path to file with format:
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
        void parsePositionsFile(const std::string& p_filename);
        private:
        std::vector<LetterPos> m_greyLetters;    ///< Letters not in word or exhausted
        std::vector<LetterPos> m_greenLetters;   ///< Letters in correct positions
        std::vector<LetterPos> m_yellowLetters;  ///< Letters in wrong positions
        
        /**
         * @brief Parse a single token like "L1" into LetterPos
         * @param p_token String containing letter and position
         * @return Parsed LetterPos structure
         */
        LetterPos parseSinglePositionString(std::string& p_token) const;
        
        /**
         * @brief Check if word satisfies green letter constraints
         * @param word Word to check
         * @return true if all green letters match
         */
        bool checkGreenLetters(const Word& p_word) const;
        
        /**
         * @brief Check if word satisfies yellow letter constraints
         * @param word Word to check
         * @return true if yellow letters exist in different positions
         */
        bool checkYellowLetters(const Word& p_word) const;
        
        /**
         * @brief Check if word satisfies grey letter constraints
         * @param p_word Word to check
         * @return true if grey letters are handled correctly
         */
        bool checkGreyLetters(const Word& p_word) const;
        
        /**
         * @brief Get minimum possible count of a letter based on constraints
         * @param p_letter Letter to check (0-25)
         * @return Minimum occurrences this letter must have
         */
        int getMinPossibleCountOfThisLetterInWord(Letter p_letter) const;
        
        /**
         * @brief Get maximum possible count of a letter based on constraints
         * @param p_letter Letter to check (0-25)
         * @return Maximum occurrences this letter can have
         */
        int getMaxPossibleCountOfThisLetterInWord(Letter p_letter) const;

        /**
         * @brief Add letter-position pair to list if not already present
         * @param letterList List to add to
         * @param lp LetterPos to add
        
        */
        void addLetterIfNotExists(std::vector<LetterPos>& letterList, const LetterPos& lp);

    };

    /**
     * @brief Convenience function to filter word list from file
     * @param p_positionFilterFilename Path to positions file
     * @param word_list Word list to filter (modified in place)
     */
    void filterOutImpossibleWords(const std::string& p_positionFilterFilename, std::vector<Word>& p_wordList);
}
 
#endif