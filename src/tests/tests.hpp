#ifndef TESTS_WORDLE_HPP
#define TESTS_WORDLE_HPP

#include "../word/word.hpp"
#include "../filter/filter.hpp"
#include <cassert>
#include <vector>

namespace Wordle
{
    void testWordClass();
    void testWordFilter();
    void testGuessingLogic();
    void runAllTests();
}

#endif