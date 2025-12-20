#ifndef _get_best_word_wordle_hpp
#define _get_best_word_wordle_hpp

#include "board/board.hpp"
#include "word/word.hpp"
#include "datatypes.hpp"
#include <vector>

namespace Wordle
{
    Word getBestWord(const std::string& positionFilterFilename = "", bool onlyGuessPossibleWords = false);
    Word getBestWordWithExistingGuesses(const std::vector<Word>& p_alreadyGuessedWords,
        const std::vector<Word>& p_wordsStillAvailableToGuess,
        const std::vector<Word>& p_wordsStillPossible);
    LongInt testWord(const Word& p_guessWord, const std::vector<Word>& p_possibleWords);
    LongInt testWordWithExistingGuesses(const Word& p_guessWord, const std::vector<Word>& p_alreadyGuessedWords, const std::vector<Word>& p_possibleWords);
    void printWordKnockout(const Word& p_word, LongInt p_numKnockouts);
}

#endif // _get_best_word_wordle_hpp
