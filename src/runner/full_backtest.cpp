#include "full_backtest.hpp"
#include "../word/create_word_list.hpp"
#include "../filter/filter.hpp"
#include "backtest.hpp"
#include "../utils/utils.hpp"
#include <iostream>
#include <fstream>

namespace Wordle
{
    std::vector<Word> filterWordsHeuristically(const std::vector<Word>& allWords)
    {
        std::vector<Word> filteredWords;
        for (const auto& word : allWords)
        {
            int vowelCount = countDistinctVowels(word.getBaseWord());
            bool doubleLetters = hasDoubleLetters(word.getBaseWord());
            if (doubleLetters) // skip words with double letters
                continue;
            if (vowelCount >= 2) // keep words with at least 2 vowels
            {
                filteredWords.push_back(word);
            }
        }
        return filteredWords;
    }
    void fullBacktest(const std::string& inputWordFilepath, const std::string& outputFilepath)
    {
        std::vector<Word> allWords = createWordList(inputWordFilepath);
        std::vector<Word> wordsToTest = filterWordsHeuristically(allWords); // too slow for full list, let's take out some probably bad ones
        std::string hardestWord;
        std::ofstream outFile(outputFilepath);
        std::string bestWord;
        double bestAverage = 100.0;
        for (const auto& word : wordsToTest)
        {
            double averageGuesses = backtestAllWords(word.getBaseWord(), false);
            std::cout << "  Starting word: " << word.getBaseWord() << " | Average guesses: " << averageGuesses << "\n";
            outFile << "Starting word: " << word.getBaseWord() << " | Average guesses: " << averageGuesses << "\n";
            if (averageGuesses < bestAverage)
            {
                bestAverage = averageGuesses;
                bestWord = word.getBaseWord();
            }
        }
        std::cout << "  Best starting word: " << bestWord << " with average guesses: " << bestAverage << "\n";
        outFile << "Best starting word: " << bestWord << " with average guesses: " << bestAverage << "\n";
    }
} // namespace Wordle