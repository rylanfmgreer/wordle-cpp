#include <iostream>
#include "src/get_best_word.hpp"

int main(int argc, char** argv)
{

    // default to wordle_positions.txt if no argument is given
    std::string positionFilterFilename = (argc > 1) ? argv[1] : "wordle_positions.txt";
    bool onlyGuessPossibleWords = true;
    Wordle::Word best_word = Wordle::getBestWord(positionFilterFilename, onlyGuessPossibleWords);
    std::cout << "Best word: " << best_word.getBaseWord() << std::endl;
    return 0;
}
