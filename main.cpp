#include <iostream>
#include "src/get_best_word.hpp"
#include "src/printing_utils/print_functions.hpp"
int main(int argc, char** argv)
{

    // default to wordle_positions.txt if no argument is given
    std::cout << std::endl << std::endl;    
    printAssetFromFilename("src/printing_utils/assets/title_asset.txt", BOLD);
    std::string positionFilterFilename = (argc > 1) ? argv[1] : "wordle_positions.txt";
    bool onlyGuessPossibleWords = true;
    Wordle::Word best_word = Wordle::getBestWord(positionFilterFilename, onlyGuessPossibleWords);
    printBestWord(best_word);
    std::cout << std::endl << std::endl;
    return 0;
}
