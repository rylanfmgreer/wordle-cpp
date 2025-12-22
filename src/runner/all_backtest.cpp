#include "all_backtest.hpp"
#include "../word/create_word_list.hpp"
#include "../filter/filter.hpp"
#include "backtest.hpp"
#include <iostream>
#include <fstream>

namespace Wordle
{
    void totalBacktest(const std::string& inputWordFilepath, const std::string& outputFilepath)
    {
        std::vector<Word> allWords = createWordList(inputWordFilepath);
        std::string hardestWord;
        std::ofstream outFile(outputFilepath);
        std::string bestWord;
        double bestAverage = 100.0;
        for (const auto& word : allWords)
        {
            double averageGuesses = backtestAllWords(word.getBaseWord(), false);
            std::cout << "Starting word: " << word.getBaseWord() << " | Average guesses: " << averageGuesses << "\n";
            outFile << "Starting word: " << word.getBaseWord() << " | Average guesses: " << averageGuesses << "\n";
            if (averageGuesses < bestAverage)
            {
                bestAverage = averageGuesses;
                bestWord = word.getBaseWord();
            }
        }
        std::cout << "Best starting word: " << bestWord << " with average guesses: " << bestAverage << "\n";
        outFile << "Best starting word: " << bestWord << " with average guesses: " << bestAverage << "\n";
    }
} // namespace Wordle