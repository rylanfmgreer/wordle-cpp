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
        SmallInt get_letter_at_position(std::size_t position) const { return letters[position]; }
        SmallInt get_letter_count(SmallInt letter) const { return letter_count[letter]; }
        inline const std::string get_base_word() const { return base_word; }
        // assignment operator
        

        private:
        const std::string base_word;
        SmallInt letters[WORD_LENGTH];
        SmallInt letter_count[ALPHABET_SIZE];
    };
}
#endif // _WORDLE_WORD_HPP___