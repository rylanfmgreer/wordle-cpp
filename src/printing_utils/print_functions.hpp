/**
 * @file print_functions.hpp
 * @brief Fancy printing utilities for Wordle solver output
 * @author Rylan Greer
 */

#ifndef PRINT_FUNCTIONS_HPP
#define PRINT_FUNCTIONS_HPP
#include "print_constants.hpp"
#include "../datatypes.hpp"
#include "../word/word.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>

namespace Wordle
{
    /**
     * @brief Print the best word with fancy formatting
     * @param best_word The optimal word to display
     */
    void printBestWord(const Wordle::Word& best_word);

    /**
     * @brief Print ASCII art from a file
     * @param filename Path to the asset file
     * @param prefix ANSI color/style prefix to apply
     * @return Number of lines printed
     */
    int printAssetFromFilename(const std::string& filename, const std::string& prefix = "");

    /**
     * @brief Print backspace characters to clear output
     * @param n Number of characters to backspace
     */
    void backspacePrint(int n);

    /**
     * @brief Blink an ASCII art asset multiple times
     * @param filename Path to the asset file
     * @param n_times Number of times to blink
     * @param delay_ms Delay between blinks in milliseconds
     * @param prefix ANSI color/style prefix to apply
     */
    void blinkAssetNTimes(const std::string& filename, int n_times, int delay_ms=500, const std::string& prefix = "");

    /**
     * @brief Generate formatted string for best word display
     * @param best_word The word to format
     * @return Formatted string with box drawing and colors
     */
    std::string generateBestWordPrintStr(const Wordle::Word& best_word);

    /**
     * @brief Print statistics about words eliminated
     * @param prefix The guessed word
     * @param n_words_knocked_out Average words eliminated
     * @param n_remaining_words Number of remaining possible words
     * @return Number of lines printed
     */
    int printNumberOfWordsKnockedOut(const std::string& prefix, Wordle::LongInt n_words_knocked_out, Wordle::LongInt n_remaining_words);

    /**
     * @brief Read emoji configuration from file
     * @param config_filepath Path to config file containing emoji
     * @return The emoji string
     */
    std::string getEmojiFromConfigValue(const std::string& config_filepath);

    /**
     * @brief Generate title bar with custom emoji
     * @param emoji The emoji to display in the title
     * @return Formatted title bar string
     */
    std::string generateTitleBar(const std::string& emoji);

    /**
     * @brief Print standard header information
     */
    void standardInitialPrints();

    /**
     * @brief Print the big frog ASCII art
     */
    inline void printBigFrog(){ printAssetFromFilename("src/printing_utils/assets/bigfrog.txt", RESET); }

    std::string getStringFromAssetFile(const std::string& filename, const std::string& prefix = "");
    
    int printStringWithRepeatingColourGradient(const std::string& str, const std::vector<std::string>& color_codes);
}  
#endif // PRINT_FUNCTIONS_HPP