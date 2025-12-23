#ifndef _all_backtest_wordle_hpp
#define _all_backtest_wordle_hpp
#include <string>
#include <vector>
#include "../word/word.hpp" 
namespace Wordle
{
    /**
     * @brief Heuristically filter words to reduce test set size
     * @param allWords Full list of words to filter
     * @return Filtered list of words likely to perform better
     */
    std::vector<Word> filterWordsHeuristically(const std::vector<Word>& allWords);

    /**
     * @brief Perform a full backtest to find the best starting word
     * @param inputWordFilepath Path to the input word list file
     * @param outputFilepath Path to the output results file
     * 
     * Tests each candidate starting word against all possible answers
     * and records average performance, writing results to the output file.
     */
    void fullBacktest(const std::string& inputWordFilepath, const std::string& outputFilepath="backtest_results.txt");
} // namespace Wordle


#endif