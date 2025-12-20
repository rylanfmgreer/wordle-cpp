#include "word.hpp"
#include "../utils/utils.hpp"
#include <cassert>

namespace Wordle
{
    Word::Word(const std::string& word)
    : base_word(word)
    {
        assert(word.length() == WORD_LENGTH);
        for(std::size_t i = 0; i < ALPHABET_SIZE; ++i)
            letter_count[i] = 0;

        for (std::size_t i = 0; i < WORD_LENGTH; ++i)
        {
            Letter int_representation = charToInt(word[i]);
            letters[i] = int_representation;
            letter_count[int_representation]++;
        }
    }

    Word& Word::operator=(const Word& other)
    {
        if (this != &other)
        {
            // Copy base_word (const_cast needed for const member)
            const_cast<std::string&>(base_word) = other.base_word;
            
            // Copy letters array
            for (std::size_t i = 0; i < WORD_LENGTH; ++i)
            {   
                letters[i] = other.letters[i];
            }
            
            // Copy letter_count array
            for (std::size_t i = 0; i < ALPHABET_SIZE; ++i)
            {
                letter_count[i] = other.letter_count[i];
            }
        }
        return *this;
    }
} // namespace Wordle
