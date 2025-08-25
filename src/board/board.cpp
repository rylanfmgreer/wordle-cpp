#include "board.hpp"

namespace Wordle
{
    Board::Board(const Word& correct_word) : correct_word(correct_word)
    {
        reset();
    }

    void Board::reset()
    {
        // set all "letter is possible" to true
        for(std::size_t i = 0; i < ALPHABET_SIZE * WORD_LENGTH; ++i)
            letter_is_possible_in_space[i] = true;

        // set all "min_letters" to 0
        for (std::size_t i(0); i < ALPHABET_SIZE; ++i) min_letters[i] = 0;

        // set all "max_letters" to WORD_LENGTH
        for (std::size_t i(0); i < ALPHABET_SIZE; ++i) max_letters[i] = WORD_LENGTH;
    }


    void Board::update_letter_is_possible_in_space_with_correct_guess(std::size_t position, SmallInt letter)
    {
        for(std::size_t i(0); i < ALPHABET_SIZE; ++i)
            if(i != letter)
            {
                letter_is_possible_in_space[get_position_in_letter_possible_space(position, i)] = false;
            }
            else
            {
                letter_is_possible_in_space[get_position_in_letter_possible_space(position, i)] = true;
            }
    }

    void Board::update_letter_is_possible_in_space_with_incorrect_guess(std::size_t position, SmallInt letter)
    {
        letter_is_possible_in_space[get_position_in_letter_possible_space(position, letter)] = false;
    }

    void Board::update_min_letters_with_guess(SmallInt letter_to_check, SmallInt count_in_guess)
    {
        // SUSPECT
        SmallInt count_in_truth = correct_word.get_letter_count(letter_to_check);
        if(count_in_truth < count_in_guess)
            min_letters[letter_to_check] = count_in_truth;
    }

    void Board::update_max_letters_with_guess(SmallInt letter_to_check, SmallInt count_in_guess)
    {
        // SUSPECT
        SmallInt count_in_truth = correct_word.get_letter_count(letter_to_check);
        if(count_in_guess > count_in_truth)
            max_letters[letter_to_check] = count_in_truth;
    }

    void Board::guess(const Word& word)
    {
        for(std::size_t i = 0; i < WORD_LENGTH; ++i)
        {
            SmallInt letter = word.get_letter_at_position(i);

            // update the positions
            bool guess_is_correct = letter == correct_word.get_letter_at_position(i);
            guess_is_correct ? update_letter_is_possible_in_space_with_correct_guess(i, letter) : update_letter_is_possible_in_space_with_incorrect_guess(i, letter);

            // update the count metrics
            SmallInt count = word.get_letter_count(letter);
            update_min_letters_with_guess(letter, count);
            update_max_letters_with_guess(letter, count);
        }
    }

    bool Board::word_could_be_solution(const Word& word) const
    {

        // check if the word fits the count constraints
        for(SmallInt letter_index = 0; letter_index < WORD_LENGTH; ++letter_index)
        {
            SmallInt letter = word.get_letter_at_position(letter_index);
            SmallInt count = word.get_letter_count(letter);
            if(count < min_letters[letter] || count > max_letters[letter])
                return false;
        }

        // check if the word fits the position constraints
        for(std::size_t i = 0; i < WORD_LENGTH; ++i)
        {
            SmallInt letter = word.get_letter_at_position(i);
            if(!letter_is_possible_in_space[get_position_in_letter_possible_space(i, letter)])
                return false;
        }

        return true;
    }

    int Board::get_number_of_potential_solutions(const std::vector<Word>& word_list) const
    {
        int count = 0;
        for (std::size_t i = 0; i < word_list.size(); ++i)
            count += word_could_be_solution(word_list[i]);
        return count;
    }

    std::vector<Word> Board::get_valid_words(const std::vector<Word>& word_list) const
    {
        std::vector<Word> valid_words;
        valid_words.reserve(word_list.size());
        for (std::size_t i = 0; i < word_list.size(); ++i)
            if(word_could_be_solution(word_list[i]))
                valid_words.push_back(word_list[i]);
        return valid_words;
    }

    Board Board::copy() const
    {
        Board new_board(correct_word);
        for(std::size_t i = 0; i < ALPHABET_SIZE * WORD_LENGTH; ++i)
            new_board.letter_is_possible_in_space[i] = letter_is_possible_in_space[i];
        for(std::size_t i = 0; i < ALPHABET_SIZE; ++i)
        {
            new_board.min_letters[i] = min_letters[i];
            new_board.max_letters[i] = max_letters[i];
        }
        return new_board;
    }
} // namespace Wordle
