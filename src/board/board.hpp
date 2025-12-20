/**
 * @file board.hpp
 * @brief Wordle game board simulation with answer tracking
 * @author Rylan Greer
 */

#ifndef _WORDLE_BOARD_HPP___
#define _WORDLE_BOARD_HPP___

#include <array>
#include "../datatypes.hpp"
#include "../word/word.hpp"
#include <vector>

namespace Wordle
{
    /**
     * @class BoardWithKnownAnswer
     * @brief Simulates a Wordle game board where the correct answer is known
     * 
     * This class tracks:
     * - Which letters can appear in which positions
     * - Minimum and maximum occurrences of each letter
     * - The correct answer for validation
     */
    class BoardWithKnownAnswer
    {
        public:
        /**
         * @brief Construct a board with a known correct word
         * @param correct_word The target word for this game
         */
        BoardWithKnownAnswer(const Word& correct_word);
        
        /**
         * @brief Copy constructor
         * @param other Board to copy from
         */
        BoardWithKnownAnswer(const BoardWithKnownAnswer& other);
        
        /**
         * @brief Reset the board to initial state
         */
        void reset();
        
        /**
         * @brief Make a guess and update board constraints
         * @param word The guessed word
         * 
         * Updates the board state based on which letters are correct,
         * present but misplaced, or absent.
         */
        void guess(const Word& word);
        
        /**
         * @brief Check if a word could be the solution given current constraints
         * @param word Word to check
         * @return true if word satisfies all constraints
         */
        bool wordCouldBeSolution(const Word& word) const;
        
        /**
         * @brief Count how many words from a list could be solutions
         * @param word_list List of words to check
         * @return Number of words that satisfy constraints
         */
        int getNumberOfPotentialSolutions(const std::vector<Word>& word_list) const;
        
        /**
         * @brief Get all valid words from a list
         * @param word_list List of words to filter
         * @return Vector of words that satisfy constraints
         */
        std::vector<Word> getValidWords(const std::vector<Word>& word_list) const;
        
        /**
         * @brief Create a copy of this board
         * @return New BoardWithKnownAnswer with identical state
         */
        BoardWithKnownAnswer copy() const;

        /**
         * @brief Add a grey (not in word) letter constraint
         * @param position Position where letter was guessed
         * @param letter Letter to mark as grey
         */
        void addGreyLetter(std::size_t position, Letter letter);
        
        /**
         * @brief Add a green (correct position) letter constraint
         * @param position Position of correct letter
         * @param letter Letter at that position
         */
        void addGreenLetter(std::size_t position, Letter letter);
        
        /**
         * @brief Add a yellow (wrong position) letter constraint
         * @param position Position where letter was guessed
         * @param letter Letter that exists elsewhere
         */
        void addYellowLetter(std::size_t position, Letter letter);
    

        private:
        Word correct_word;                                        ///< The target word
        bool letter_is_possible_in_space[ALPHABET_SIZE * WORD_LENGTH];  ///< Letter possibility matrix
        Letter min_letters[ALPHABET_SIZE];                        ///< Minimum occurrences per letter
        Letter max_letters[ALPHABET_SIZE];                        ///< Maximum occurrences per letter

        /**
         * @brief Convert position and letter to index in possibility array
         * @param row Position in word (0-4)
         * @param letter Letter (0-25)
         * @return Index in letter_is_possible_in_space array
         */
        inline std::size_t getPositionInLetterPossibleSpace(std::size_t row, Letter letter) const {return letter * WORD_LENGTH + row;}
        
        /**
         * @brief Update possibilities when a letter is guessed correctly
         * @param position Position of correct guess
         * @param letter Letter that was correct
         */
        void updateLetterIsPossibleInSpaceWithCorrectGuess(std::size_t position, Letter letter);
        
        /**
         * @brief Update possibilities when a letter is guessed incorrectly
         * @param position Position of incorrect guess
         * @param letter Letter that was incorrect at this position
         */
        void updateLetterIsPossibleInSpaceWithIncorrectGuess(std::size_t position, Letter letter);
        
        /**
         * @brief Update minimum letter count based on guess feedback
         * @param letter_to_check Letter to update
         * @param count_in_guess Count of this letter in the guess
         */
        void updateMinLettersWithGuess(Letter letter_to_check, Letter count_in_guess);
        
        /**
         * @brief Update maximum letter count based on guess feedback
         * @param letter_to_check Letter to update
         * @param count_in_guess Count of this letter in the guess
         */
        void updateMaxLettersWithGuess(Letter letter_to_check, Letter count_in_guess);

    };
}
#endif // _WORDLE_BOARD_HPP___