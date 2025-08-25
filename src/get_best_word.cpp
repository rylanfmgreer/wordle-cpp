#include "get_best_word.hpp"
#include "word/create_word_list.hpp"
#include "board/board.hpp"
#include <iostream>

namespace Wordle
{

    LongInt test_word(const Word& guess_word, const std::vector<Word>& possible_words)
    {
        LongInt score = 0;
        for(std::size_t target_word_index(0); target_word_index < possible_words.size(); ++target_word_index)
        {
            Board board(possible_words[target_word_index]);
            board.guess(guess_word);
            score += board.get_number_of_potential_solutions(possible_words);
        }
        return score;
    }

    Word get_best_word()
    {
        std::vector<Word> possible_words = create_word_list();
        LongInt infinity = possible_words.size() * possible_words.size() + 1;
        LongInt best_word_index = 0;
        LongInt best_score = infinity;
        int average_KO = 0.0;

        for(std::size_t guess_word_index(0); guess_word_index < possible_words.size(); ++guess_word_index)
        {
            average_KO = (infinity - 1 - best_score) / possible_words.size();
            // std::cout << "Guessing word: " << possible_words[guess_word_index].get_base_word() << ", " << "Best seen so far: " << possible_words[best_word_index].get_base_word() << ", Average KO: " << average_KO << '\n';
            LongInt this_score = test_word(possible_words[guess_word_index], possible_words);
            if(this_score < best_score)
            {
                best_score = this_score;
                best_word_index = guess_word_index;
            }
            average_KO = (infinity - 1 - this_score) / possible_words.size();
            std::cout << "Guessing word: " << possible_words[guess_word_index].get_base_word() << " knocks out " << average_KO << " words on average\n";

        }

        return possible_words[best_word_index];
    }
}
