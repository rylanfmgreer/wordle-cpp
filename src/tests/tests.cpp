#include "tests.hpp"
#include "../word/word.hpp"
#include "../filter/filter.hpp"
#include "../runner/get_best_word.hpp"
#include <iostream>

namespace Wordle
{
    void testWordClass()
    {
        Word testWord("apple");
        assert(testWord.getBaseWord() == "apple");
        assert(testWord.getLetterAtPosition(0) == 0); // 'a'
        assert(testWord.getLetterAtPosition(1) == 15); // 'p'
        assert(testWord.getLetterCount(15) == 2); // 'p' appears twice
        assert(testWord.getLetterCount(0) == 1); // 'a' appears once
        assert(testWord.getLetterCount(11) == 1); // 'l' appears once
        assert(testWord.getLetterCount(4) == 1); // 'e' appears once
        assert(testWord.getLetterCount(2) == 0); // 'c' does not appear
    }

    void testWordFilter()
    {
        std::vector<Word> wordList = { Word("apple"), Word("grape"), Word("berry"), Word("melon"), Word("peach") };
        WordFilter filter;
        filter.addGreenLetter(0, 15); // 'p' at position 0
        filter.addYellowLetter(1, 0); // 'a' not at position 1
        filter.addGreyLetter(2, 4); // 'e' not in word

        std::vector<Word> filteredWords = filter.filterWordList(wordList);
        assert(filteredWords.size() == 1);
        assert(filteredWords[0].getBaseWord() == "peach");
    }

    void testGuessingLogic()
    {
        std::vector<Word> wordList = { Word("apple"), Word("grape"), Word("berry"), Word("melon"), Word("peach") };
        Word guessWord("grape");
        LongInt score = testWord(guessWord, wordList);
        assert(score > 0); // Basic check to ensure scoring works
    }

    void testFullGuessingLogic()
    {
        std::vector<Word> wordList = { Word("apple"), Word("grape"), Word("berry"), Word("melon"), Word("peach") };
        
    }

    void runAllTests()
    {
        testWordClass();
        testWordFilter();
        testGuessingLogic();
        std::cout << "All tests passed successfully!\n";
    }
}