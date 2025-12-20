#include <iostream>
#include "src/get_best_word.hpp"
#include "src/printing_utils/print_functions.hpp"
int main(int argc, char** argv)
{

    // default to wordle_positions.txt if no argument is given
    std::cout << std::endl << std::endl;    
    printAssetFromFilename("src/printing_utils/assets/title_asset.txt", BOLD);
    printAssetFromFilename("src/printing_utils/assets/copyright_info.txt", RESET);
    //printAssetFromFilename("src/printing_utils/assets/how_to_use.txt");
    std::string positionFilterFilename = (argc > 1) ? argv[1] : "wordle_positions.txt";
    bool onlyGuessPossibleWords = true;
    Wordle::WordScore best_word_score = Wordle::getBestWord(positionFilterFilename, onlyGuessPossibleWords);
    printBestWord(best_word_score.word);
    printNumberOfWordsKnockedOut(best_word_score.word.getBaseWord(), best_word_score.numRemainingWords, best_word_score.averageKnockout);
    std::cout << std::endl << std::endl;
    return 0;
}
