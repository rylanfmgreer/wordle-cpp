#ifndef PRINT_FUNCTIONS_HPP
#define PRINT_FUNCTIONS_HPP
#include "print_constants.hpp"
#include "../word/word.hpp"
#include <iostream>
#include <fstream>
#include <string>

void printBestWord(const Wordle::Word& best_word)
{
    std::cout << "\n";
    std::cout << TOP_BAR << "\n";
    std::cout << TITLE_BAR << "\n";

    std::cout << MID_BAR << "\n";
    std::cout << BAR_FORMAT<< "  ║" << RESET << "             " << BOLD << GREEN << MAGENTA << best_word.getBaseWord() << RESET << "              " << BAR_FORMAT<< "║" << RESET << "\n";
    std::cout << BOT_BAR << "\n";
    std::cout << "\n";
}

void printAssetFromFilename(const std::string& filename, const std::string& prefix = "")
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    std::string line;
    std::cout << prefix;
    while (std::getline(file, line))
    {
        std::cout <<prefix <<  line << "\n";
    }

    file.close();
}

#endif // PRINT_FUNCTIONS_HPP