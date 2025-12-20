/**
 * @file create_word_list.hpp
 * @brief Utilities for loading word lists from files
 * @author Rylan Greer
 */

#ifndef _create_word_list_wordle_hpp
#define _create_word_list_wordle_hpp

#include "word.hpp"
#include <vector>

namespace Wordle
{
    /**
     * @brief Create a list of Words from a text file
     * @param filename Path to file with one word per line
     * @return Vector of Word objects loaded from the file
     * 
     * Reads a text file where each line contains a single word
     * and creates a Word object for each line.
     */
    std::vector<Word> createWordList(const std::string& filename="src/small_word_list.txt");
}

#endif // _create_word_list_wordle_hpp