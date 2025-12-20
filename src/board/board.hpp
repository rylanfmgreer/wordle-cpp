#ifndef _WORDLE_BOARD_HPP___
#define _WORDLE_BOARD_HPP___

#include <array>
#include "../datatypes.hpp"
#include "../word/word.hpp"
#include <vector>

namespace Wordle
{
    class BoardWithKnownAnswer
    {
        public:
        BoardWithKnownAnswer(const Word& correct_word);
        BoardWithKnownAnswer(const BoardWithKnownAnswer& other);
        void reset();
        void guess(const Word& word);
        bool wordCouldBeSolution(const Word& word) const;
        int getNumberOfPotentialSolutions(const std::vector<Word>& word_list) const;
        std::vector<Word> getValidWords(const std::vector<Word>& word_list) const;
        BoardWithKnownAnswer copy() const;

        void addGreyLetter(std::size_t position, Letter letter);
        void addGreenLetter(std::size_t position, Letter letter);
        void addYellowLetter(std::size_t position, Letter letter);
    

        private:
        Word correct_word;
        bool letter_is_possible_in_space[ALPHABET_SIZE * WORD_LENGTH];
        Letter min_letters[ALPHABET_SIZE];
        Letter max_letters[ALPHABET_SIZE];

        inline std::size_t getPositionInLetterPossibleSpace(std::size_t row, Letter letter) const {return letter * WORD_LENGTH + row;}
        void updateLetterIsPossibleInSpaceWithCorrectGuess(std::size_t position, Letter letter);
        void updateLetterIsPossibleInSpaceWithIncorrectGuess(std::size_t position, Letter letter);
        void updateMinLettersWithGuess(Letter letter_to_check, Letter count_in_guess);
        void updateMaxLettersWithGuess(Letter letter_to_check, Letter count_in_guess);

    };
}
#endif // _WORDLE_BOARD_HPP___