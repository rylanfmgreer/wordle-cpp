/**
 * @file daily_run.hpp
 * @brief Main entry point for daily Wordle solving
 * @author Rylan Greer
 */

#ifndef _daily_run_wordle_hpp
#define _daily_run_wordle_hpp
#include <iostream>
#include "get_best_word.hpp"
#include "backtest.hpp"
#include "../printing_utils/print_functions.hpp"
namespace Wordle
{

    /**
     * @brief Main function for daily Wordle solving with fancy output
     * @param argc Number of command line arguments
     * @param argv Command line arguments array
     * 
     * Displays the title screen and copyright info, then finds and prints
     * the best word to guess based on the provided position filter file
     * (defaults to "wordle_positions.txt" if not specified).
     */
    void dailyRun(int argc, char** argv);

    
} // namespace Wordle

#endif