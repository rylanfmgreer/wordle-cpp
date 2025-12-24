#include "daily_run.hpp"
namespace Wordle
{
    void dailyRun(int argc, char** argv)
    {
        std::cout << std::endl << std::endl;    
        standardInitialPrints();
        //printAssetFromFilename("../printing_utils/assets/how_to_use.txt");
        std::string positionFilterFilename = (argc > 1) ? argv[1] : "wordle_positions.txt";
        bool onlyGuessPossibleWords = true;
        Wordle::WordResult bestWordResult = Wordle::getBestWord(positionFilterFilename, onlyGuessPossibleWords);
        printBestWord(bestWordResult.word);
        printNumberOfWordsKnockedOut(bestWordResult.word.getBaseWord(), bestWordResult.numRemainingWords, bestWordResult.averageKnockout);
        std::cout << std::endl << std::endl;
    }
}