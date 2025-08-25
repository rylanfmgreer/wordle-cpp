#ifndef _create_word_list_wordle_hpp
#define _create_word_list_wordle_hpp

#include "word.hpp"
#include <vector>

namespace Wordle
{
    std::vector<Word> create_word_list(const std::string& filename="src/word_list.txt");
}

#endif // _create_word_list_wordle_hpp