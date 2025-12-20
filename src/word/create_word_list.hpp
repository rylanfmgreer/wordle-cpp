#ifndef _create_word_list_wordle_hpp
#define _create_word_list_wordle_hpp

#include "word.hpp"
#include <vector>

namespace Wordle
{
    std::vector<Word> createWordList(const std::string& filename="src/small_word_list.txt");
}

#endif // _create_word_list_wordle_hpp