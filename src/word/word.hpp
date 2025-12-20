#ifndef _WORDLE_WORD_HPP___
#define _WORDLE_WORD_HPP___

#include <array>
#include <string>
#include "../datatypes.hpp"

namespace Wordle
{
    class Word
    {
        public:
        Word(const std::string& word);
        Word& operator=(const Word& other);
        Letter getLetterAtPosition(std::size_t position) const { return letters[position]; }
        Letter getLetterCount(Letter letter) const { return letter_count[letter]; }
        inline const std::string getBaseWord() const { return base_word; }

        private:
        const std::string base_word;
        Letter letters[WORD_LENGTH];
        Letter letter_count[ALPHABET_SIZE];
    };
}
#endif // _WORDLE_WORD_HPP___