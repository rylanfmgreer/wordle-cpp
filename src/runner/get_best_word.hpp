/**
 * @file get_best_word.hpp
 * @brief Core algorithm for finding optimal Wordle guesses
 * @author Rylan Greer
 */

#ifndef _get_best_word_wordle_hpp
#define _get_best_word_wordle_hpp

#include "../board/board.hpp"
#include "../word/word.hpp"
#include "../datatypes.hpp"
#include <vector>

namespace Wordle
{
    struct WordResult
    {
        Word word;
        LongInt averageKnockout;
        LongInt numRemainingWords;
        WordResult(const Word& p_word, LongInt p_averageKnockout, LongInt p_numRemainingWords=0)
            : word(p_word), averageKnockout(p_averageKnockout), numRemainingWords(p_numRemainingWords) {}
        WordResult() : word("-----"), averageKnockout(0), numRemainingWords(0) {}
    };

    /**
     * @brief Find the best word to guess given optional constraints
     * @param positionFilterFilename Path to file with known letter positions (optional)
     * @param onlyGuessPossibleWords If true, only consider words that could be the answer
     * @return The optimal word to guess
     * 
     * Analyzes all possible words and selects the one that eliminates
     * the most candidates on average.
     */
    WordResult getBestWord(const std::string& positionFilterFilename = "", bool onlyGuessPossibleWords = false, bool verbose = false);
    
    /**
     * @brief Find best word given already-guessed words
     * @param p_alreadyGuessedWords Words that have already been guessed
     * @param p_wordsStillAvailableToGuess Words that can still be guessed
     * @param p_wordsStillPossible Words that could still be the answer
     * @param verbose If true, print progress information
     * @return The optimal next word to guess
     */
    WordResult getBestWordWithExistingGuesses(const std::vector<Word>& p_alreadyGuessedWords,
        const std::vector<Word>& p_wordsStillAvailableToGuess,
        const std::vector<Word>& p_wordsStillPossible,
        bool verbose = true);
    
    /**
     * @brief Test how many words a guess would eliminate on average
     * @param p_guessWord The word to test
     * @param p_possibleWords Words that could be the answer
     * @return Average number of words eliminated by this guess
     */
    LongInt testWord(const Word& p_guessWord, const std::vector<Word>& p_possibleWords);
    
    /**
     * @brief Test word effectiveness with existing guess history
     * @param p_guessWord The word to test
     * @param p_alreadyGuessedWords Previously guessed words
     * @param p_possibleWords Words that could still be the answer
     * @return Average number of words eliminated by this guess
     */
    LongInt testWordWithExistingGuesses(const Word& p_guessWord, const std::vector<Word>& p_alreadyGuessedWords, const std::vector<Word>& p_possibleWords);
    
    /**
     * @brief Print word effectiveness information
     * @param p_word The word being evaluated
     * @param p_numKnockouts Number of words eliminated on average
     */
    void printWordKnockout(const Word& p_word, LongInt p_numKnockouts);
}

#endif // _get_best_word_wordle_hpp
