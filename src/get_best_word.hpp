#ifndef _get_best_word_wordle_hpp
#define _get_best_word_wordle_hpp

#include "board/board.hpp"
#include "word/word.hpp"
#include "datatypes.hpp"
#include <vector>

namespace Wordle
{
    Word get_best_word();
    LongInt test_word(const Word& guess_word, const std::vector<Word>& possible_words);
}

#endif // _get_best_word_wordle_hpp
