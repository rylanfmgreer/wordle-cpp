#ifndef WORDLE_BACKTEST_HPP
#define WORDLE_BACKTEST_HPP
#include <string>
namespace Wordle
{
    const std::string startingWord = "raise";
    int backtest(const std::string& finalWord, const std::string& startWord=startingWord);
    void backtestAllWords(const std::string& startWord=startingWord);
} // namespace Wordle

#endif