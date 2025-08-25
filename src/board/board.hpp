#ifndef _WORDLE_BOARD_HPP___
#define _WORDLE_BOARD_HPP___

#include <array>
#include "../datatypes.hpp"
#include "../word/word.hpp"
#include <vector>

namespace Wordle
{
    class Board {
        public:
        Board(const Word& correct_word);
        void reset();
        void guess(const Word& word);
        bool word_could_be_solution(const Word& word) const;
        int get_number_of_potential_solutions(const std::vector<Word>& word_list) const;
        std::vector<Word> get_valid_words(const std::vector<Word>& word_list) const;
        Board copy() const;

        private:
        Word correct_word;
        bool letter_is_possible_in_space[ALPHABET_SIZE * WORD_LENGTH];
        SmallInt min_letters[ALPHABET_SIZE];
        SmallInt max_letters[ALPHABET_SIZE];

        inline std::size_t get_position_in_letter_possible_space(std::size_t row, SmallInt letter) const {return letter * WORD_LENGTH + row;}
        void update_letter_is_possible_in_space_with_correct_guess(std::size_t position, SmallInt letter);
        void update_letter_is_possible_in_space_with_incorrect_guess(std::size_t position, SmallInt letter);
        void update_min_letters_with_guess(SmallInt letter_to_check, SmallInt count_in_guess);
        void update_max_letters_with_guess(SmallInt letter_to_check, SmallInt count_in_guess);

    };
}
#endif // _WORDLE_BOARD_HPP___