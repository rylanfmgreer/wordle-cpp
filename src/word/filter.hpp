#ifndef _WORDLE_WORD_FILTER_HPP___
#define _WORDLE_WORD_FILTER_HPP___

#include "word.hpp"
#include "../datatypes.hpp"
#include <vector>
#include <string>

namespace Wordle
{
    struct LetterPos
    {
        std::size_t position;
        Letter letter;
    };

    class WordFilter
    {

        public:
        std::vector<Word> filterWordList(const std::vector<Word>& word_list) const;
        bool isWordValid(const Word& word) const;
        inline void addGreenLetter(std::size_t position, Letter letter){m_greenLetters.push_back({position, letter});}
        inline void addYellowLetter(std::size_t position, Letter letter){m_yellowLetters.push_back({position, letter});}
        inline void addGreyLetter(std::size_t position, Letter letter){m_greyLetters.push_back({position, letter});}

        // Parse a file in the format:
        // green:
        // L1 E2 T3
        // yellow:
        // A4
        // grey:
        // R1 S2
        void parsePositionsFile(const std::string& filename);        private:
        std::vector<LetterPos> m_greyLetters;
        std::vector<LetterPos> m_greenLetters;
        std::vector<LetterPos> m_yellowLetters;
        LetterPos parseSinglePositionString(std::string& token) const;
        bool checkGreenLetters(const Word& word) const;
        bool checkYellowLetters(const Word& word) const;
        bool checkGreyLetters(const Word& word) const;
        int getMinPossibleCountOfThisLetterInWord(Letter letter) const;
        int getMaxPossibleCountOfThisLetterInWord(Letter letter) const;

    };

    void filterOutImpossibleWords(const std::string& positionFilterFilename, std::vector<Word>& word_list);
}
 
#endif