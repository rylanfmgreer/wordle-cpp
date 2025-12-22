#ifndef _all_backtest_wordle_hpp
#define _all_backtest_wordle_hpp
#include <string>
namespace Wordle
{
    void totalBacktest(const std::string& inputWordFilepath, const std::string& outputFilepath="backtest_results.txt");
} // namespace name


#endif