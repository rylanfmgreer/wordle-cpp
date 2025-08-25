#include "word.hpp"
#include "../utils/utils.hpp"
namespace Wordle
{
    Word::Word(const std::string& word)
    : base_word(word)
    {
        for(std::size_t i = 0; i < ALPHABET_SIZE; ++i)
            letter_count[i] = 0;

        for (std::size_t i = 0; i < WORD_LENGTH; ++i)
        {
            SmallInt int_representation = char_to_int(word[i]);
            letters[i] = int_representation;
            letter_count[int_representation]++;
        }
    }
} // namespace Wordle
