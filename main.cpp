#include <iostream>
#include "src/runner/get_best_word.hpp"
#include "src/runner/backtest.hpp"
#include "src/printing_utils/print_functions.hpp"
#include "src/runner/daily_run.hpp"
#include "src/runner/backtest.hpp"
#include "src/utils/utils.hpp"
#include <string>
int main(int argc, char** argv)
{
    std::string RunMode = "daily";
    // check to see if one of the args is "backtest"
    for(int i = 1; i < argc; ++i)
    {
        std::string arg = Wordle::toLowerCase(argv[i]);
        if(arg == "backtest")
        {
            RunMode = "backtest";
            break;
        }
    }

    if(RunMode == "backtest")
    {
        // find the word to backtest against, default to "raise"
        std::string startWord = "raise";
        if(argc > 2)
        {
            startWord = Wordle::toLowerCase(argv[2]);
        }
        Wordle::standardInitialPrints();
        Wordle::backtestAllWords(startWord);
    }
    else
    {
        Wordle::dailyRun(argc, argv);
    }
}