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

void printBestWord(const Wordle::Word& best_word);
int printAssetFromFilename(const std::string& filename, const std::string& prefix = "");
void backspacePrint(int n);
void blinkAssetNTimes(const std::string& filename, int n_times, int delay_ms=500, const std::string& prefix = "");
std::string generateBestWordPrintStr(const Wordle::Word& best_word);
int printNumberOfWordsKnockedOut(const std::string& prefix, Wordle::LongInt n_words_knocked_out, Wordle::LongInt n_remaining_words);
std::string getEmojiFromConfigValue(const std::string& config_filepath);
std::string generateTitleBar(const std::string& emoji);
#endif // PRINT_FUNCTIONS_HPP