#include "backtest.hpp"
#include "../word/create_word_list.hpp"
#include "../filter/filter.hpp"
#include "get_best_word.hpp"
#include "../printing_utils/print_functions.hpp"
#include <iostream>
namespace Wordle
{
    int backtest(const std::string& finalWord, const std::string& startingWord)
    {
        std::vector<Word> allWords = createWordList();
    
        Word answer(finalWord);
        Wordle::Word currentGuess(startingWord);
    
        WordFilter filter;
        filter.updateWithGuess(currentGuess, answer);
        std::vector<Word> possibleWords = filter.filterWordList(allWords);
        int numGuesses = 1;

        // dummy result object
        WordResult result(currentGuess, 0);
        while (possibleWords.size() > 1)
        {
            WordResult result = getBestWordWithExistingGuesses({}, possibleWords, possibleWords,false );
            currentGuess = result.word;
            filter.updateWithGuess(currentGuess, answer);
            possibleWords = filter.filterWordList(possibleWords);
            numGuesses++;
        }

        // deal with the fact that we may not have guessed the final word yet
        if(currentGuess.getBaseWord() != answer.getBaseWord())
            numGuesses++;
        
        return numGuesses;
    }

    double backtestAllWords(const std::string& startWord, bool verbose)
    {
        if (verbose)
            standardInitialPrints();
        std::cout << "\nStarting full backtest using starting word: " << startWord << "\n\n";
        printBigFrog();
        std::vector<Word> allWords = createWordList();
        LongInt totalGuesses = 0;
        LongInt maxGuesses = 0;
        std::string hardestWord;
        for (const auto& word : allWords)
        {
            int numGuesses = backtest(word.getBaseWord(), startWord);
            totalGuesses += numGuesses;
            if (numGuesses > maxGuesses)
            {
                maxGuesses = numGuesses;
                hardestWord = word.getBaseWord();
            }
            //std::cout << "Word: " << word.getBaseWord() << " guessed in " << numGuesses << " tries.\n";
        }
        double averageGuesses = static_cast<double>(totalGuesses) / allWords.size();
        std::cout << "  \nAverage number of guesses: " << averageGuesses << "\n";
        std::cout << "  Hardest word: " << hardestWord << " with " << maxGuesses << " guesses.\n";
        return averageGuesses;
    }
    
} // namespace Wordle
