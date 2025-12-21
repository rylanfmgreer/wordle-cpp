/**
 * @file backtest.hpp
 * @brief Backtesting utilities for evaluating Wordle solver performance
 * @author Rylan Greer
 */

#ifndef WORDLE_BACKTEST_HPP
#define WORDLE_BACKTEST_HPP
#include <string>
namespace Wordle
{
    /** @brief Default starting word for backtests */
    const std::string startingWord = "raise";
    
    /**
     * @brief Test solver performance on a specific word
     * @param finalWord The target word to solve
     * @param startWord Starting word for the test (defaults to "raise")
     * @return Number of guesses required to solve
     * 
     * Simulates solving a Wordle puzzle starting from a given word
     * and tracks how many guesses are needed to reach the target.
     */
    int backtest(const std::string& finalWord, const std::string& startWord=startingWord);
    
    /**
     * @brief Run backtest on all words in the word list
     * @param startWord Starting word for all tests (defaults to "raise")
     * @param verbose If true, the header image
     * 
     * Tests the solver against every possible target word and reports
     * statistics on performance (average guesses, distribution, etc.).
     */
    void backtestAllWords(const std::string& startWord=startingWord, bool verbose=true);
} // namespace Wordle

#endif