#include "get_best_word.hpp"
#include "../word/create_word_list.hpp"
#include "../board/board.hpp"
#include <iostream>
#include "../filter/filter.hpp"
#include <string>

namespace Wordle
{

    void printWordKnockout(const Word& word, LongInt ko)
    {
        const std::string BOLD = "\033[1m";
        const std::string MAGENTA = "\033[35m";
        const std::string RESET = "\033[0m";
        
        std::cout << "  " << BOLD + MAGENTA << word.getBaseWord() << RESET << " knocks out " << BOLD << ko << RESET << " words on average\n";
    }

    WordResult getBestWordWithExistingGuesses(const std::vector<Word>& p_alreadyGuessedWords,
        const std::vector<Word>& p_wordsAvailableToGuess,
        const std::vector<Word>& p_wordsThatAreStillPossible,
        bool verbose)
    {
        LongInt infinity = p_wordsThatAreStillPossible.size() * p_wordsThatAreStillPossible.size() + 1;
        std::size_t best_word_index = 0;
        LongInt best_score = infinity;
        WordResult bestWordResult(p_wordsThatAreStillPossible[0], 0, p_wordsThatAreStillPossible.size());

        for(std::size_t guess_word_index(0); guess_word_index < p_wordsAvailableToGuess.size(); ++guess_word_index)
        {
            // guess the word and see how it does
            const Word& guess_word = p_wordsAvailableToGuess[guess_word_index];
            LongInt this_score = testWordWithExistingGuesses(guess_word, p_alreadyGuessedWords, p_wordsThatAreStillPossible);
            int average_KO = (infinity - 1 - this_score) / p_wordsThatAreStillPossible.size();
            if(this_score < bestWordResult.averageKnockout)
                bestWordResult = WordResult(guess_word, average_KO, p_wordsThatAreStillPossible.size()); 
            if(verbose) printWordKnockout(p_wordsAvailableToGuess[guess_word_index], average_KO);
        }
        return bestWordResult;
    }
    LongInt testWordWithExistingGuesses(const Word& guess_word, const std::vector<Word>& already_guessed_words, const std::vector<Word>& possible_words)
    {
        LongInt score = 0;
        for(std::size_t target_word_index(0); target_word_index < possible_words.size(); ++target_word_index)
        {
            BoardWithKnownAnswer board(possible_words[target_word_index]);
            for(std::size_t already_guessed_word_index(0); already_guessed_word_index < already_guessed_words.size(); ++already_guessed_word_index)
            {
                board.guess(already_guessed_words[already_guessed_word_index]);
            }
            board.guess(guess_word);
            score += board.getNumberOfPotentialSolutions(possible_words);
        }
        return score;
    }

    LongInt testWord(const Word& guess_word, const std::vector<Word>& possible_words)
    {
        std::vector<Word> already_guessed_words;
        return testWordWithExistingGuesses(guess_word, already_guessed_words, possible_words);
    }

    WordResult getBestWord(const std::string& positionFilterFilename, bool onlyGuessPossibleWords, bool verbose)
    {
        std::vector<Word> wordsAvailableToGuess = createWordList();
        std::vector<Word> possibleWords(wordsAvailableToGuess);
        
        if(positionFilterFilename != "")
            filterOutImpossibleWords(positionFilterFilename, possibleWords);

        if(onlyGuessPossibleWords)
            wordsAvailableToGuess = possibleWords;
        
        WordResult best_word_score = getBestWordWithExistingGuesses({},
            wordsAvailableToGuess,
            possibleWords,
            verbose);
        return best_word_score;
    }

}
