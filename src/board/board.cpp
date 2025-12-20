#include "board.hpp"

namespace Wordle
{
    BoardWithKnownAnswer::BoardWithKnownAnswer(const Word& correct_word) : correct_word(correct_word)
    {
        reset();
    }

    BoardWithKnownAnswer::BoardWithKnownAnswer(const BoardWithKnownAnswer& other) : correct_word(other.correct_word)
    {
        // Copy the state of the other board
        std::copy(other.letter_is_possible_in_space,
            other.letter_is_possible_in_space + (ALPHABET_SIZE * WORD_LENGTH),
            letter_is_possible_in_space);
        std::copy(other.min_letters, other.min_letters + ALPHABET_SIZE, min_letters);
        std::copy(other.max_letters, other.max_letters + ALPHABET_SIZE, max_letters);
    }

    void BoardWithKnownAnswer::reset()
    {
        /*
            Default values are:
            -- letter_is_possible_in_space: true
            -- min_letters: 0
            -- max_letters: WORD_LENGTH
        */
        std::fill(letter_is_possible_in_space, letter_is_possible_in_space + (ALPHABET_SIZE * WORD_LENGTH), true);
        std::fill(min_letters, min_letters + ALPHABET_SIZE, 0);
        std::fill(max_letters, max_letters + ALPHABET_SIZE, WORD_LENGTH);
    }


    void BoardWithKnownAnswer::updateLetterIsPossibleInSpaceWithCorrectGuess(std::size_t position, Letter letter)
    {
        /*
            If we guess correct, put all other letters as impossible in this position
            but keep the letter we have.
        */
        std::size_t idx = position;
        for(std::size_t i(0); i < ALPHABET_SIZE; ++i)
        {
            (i != letter) ? letter_is_possible_in_space[idx] = false : letter_is_possible_in_space[idx] = true;
            idx += WORD_LENGTH;
        }
    }

    void BoardWithKnownAnswer::updateLetterIsPossibleInSpaceWithIncorrectGuess(std::size_t position, Letter letter)
    {
        // Two cases:
        // 1. The letter has not appeared in the correct word at all -> mark it as impossible in all positions
        letter_is_possible_in_space[getPositionInLetterPossibleSpace(position, letter)] = false;
    }

    void BoardWithKnownAnswer::updateMinLettersWithGuess(Letter letter_to_check, Letter count_in_guess)
    {
        /*
            TODO: revisit as I think this approach is suspect
        */
        Letter count_in_truth = correct_word.getLetterCount(letter_to_check);
        if(count_in_truth < count_in_guess)
            min_letters[letter_to_check] = count_in_truth;
    }

    void BoardWithKnownAnswer::updateMaxLettersWithGuess(Letter letter_to_check, Letter count_in_guess)
    {
        /*
            TODO: revisit as I think this approach is suspect
        */
        Letter count_in_truth = correct_word.getLetterCount(letter_to_check);
        if(count_in_guess > count_in_truth)
            max_letters[letter_to_check] = count_in_truth;
    }

    void BoardWithKnownAnswer::guess(const Word& word)
    {
        for(std::size_t i = 0; i < WORD_LENGTH; ++i)
        {
            Letter letter = word.getLetterAtPosition(i);

            // update the positions
            bool guess_is_correct = letter == correct_word.getLetterAtPosition(i);
            guess_is_correct ? updateLetterIsPossibleInSpaceWithCorrectGuess(i, letter) : updateLetterIsPossibleInSpaceWithIncorrectGuess(i, letter);

            // update the count metrics
            Letter count = word.getLetterCount(letter);
            updateMinLettersWithGuess(letter, count);
            updateMaxLettersWithGuess(letter, count);
        }
    }

    bool BoardWithKnownAnswer::wordCouldBeSolution(const Word& word) const
    {

        // check if the word fits the count constraints
        for(std::size_t letter_index = 0; letter_index < WORD_LENGTH; ++letter_index)
        {
            Letter letter = word.getLetterAtPosition(letter_index);
            Letter count = word.getLetterCount(letter);
            if(count < min_letters[letter] || count > max_letters[letter])
                return false;
            if(!letter_is_possible_in_space[getPositionInLetterPossibleSpace(letter_index, letter)])
                return false;
        }
        return true;
    }

    int BoardWithKnownAnswer::getNumberOfPotentialSolutions(const std::vector<Word>& word_list) const
    {
        int count = 0;
        for (std::size_t i = 0; i < word_list.size(); ++i)
            count += wordCouldBeSolution(word_list[i]);
        return count;
    }

    std::vector<Word> BoardWithKnownAnswer::getValidWords(const std::vector<Word>& word_list) const
    {
        std::vector<Word> valid_words;
        valid_words.reserve(word_list.size());
        for (std::size_t i = 0; i < word_list.size(); ++i)
            if(wordCouldBeSolution(word_list[i]))
                valid_words.push_back(word_list[i]);
        return valid_words;
    }

    BoardWithKnownAnswer BoardWithKnownAnswer::copy() const
    {
        return BoardWithKnownAnswer(*this);
    }

} // namespace Wordle