#include "filter.hpp"
#include "../utils/utils.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

namespace Wordle
{
    void filterOutImpossibleWords(const std::string& positionFilterFilename, std::vector<Word>& word_list)
    {
        WordFilter filter;
        filter.parsePositionsFile(positionFilterFilename);
        word_list = filter.filterWordList(word_list);
    }
    std::vector<Word> WordFilter::filterWordList(const std::vector<Word>& word_list) const
    {
        std::vector<Word> filtered_words;
        for (const auto& word : word_list)
        {
            if(word.getBaseWord() == "myrrh")
                bool debug = true;
            bool thisValid = isWordValid(word);
            if (thisValid)
            {
                filtered_words.push_back(word);
            }
        }
        return filtered_words;
    }

    bool WordFilter::checkGreenLetters(const Word& word) const
    {
        for (const auto& lp : m_greenLetters)
        {
            if (word.getLetterAtPosition(lp.position) != lp.letter)
                return false;
        }
        return true;
    }
    bool WordFilter::checkYellowLetters(const Word& word) const
    {
        for (const auto& lp : m_yellowLetters)
        {
            if (word.getLetterAtPosition(lp.position) == lp.letter)
                return false;
            if (word.getLetterCount(lp.letter) == 0)
                return false;
        }
        return true;
    }

    int WordFilter::getMinPossibleCountOfThisLetterInWord(Letter letter) const
    {
        int possibleCount = 0;
        for (const auto& lp : m_greenLetters)
        {
            if (lp.letter == letter)
                possibleCount++;
        }
        for (const auto& lp : m_yellowLetters)
        {
            if (lp.letter == letter)
                possibleCount++;
        }
        return possibleCount;
    }

    int WordFilter::getMaxPossibleCountOfThisLetterInWord(Letter letter) const
    {
        int possibleCount = WORD_LENGTH; // max possible in a 5-letter word
        for (const auto& lp : m_greyLetters)
        {
            if (lp.letter == letter)
                possibleCount = getMinPossibleCountOfThisLetterInWord(letter);
        }
        return possibleCount;
    }

    bool WordFilter::checkGreyLetters(const Word& word) const
    {

        // filter 2: check positions and count
        for (const auto& lp : m_greyLetters)
        {
            int thisWordLc = word.getLetterCount(lp.letter);
            int possibleMinLc = getMinPossibleCountOfThisLetterInWord(lp.letter);
            int possibleMaxLc = getMaxPossibleCountOfThisLetterInWord(lp.letter); // grey letters imply max count is min count
            if (thisWordLc < possibleMinLc)
                return false;
            if (thisWordLc > possibleMaxLc)
                return false;

            if (word.getLetterAtPosition(lp.position) == lp.letter)
                return false;
        }
        return true;
    }

    bool WordFilter::isWordValid(const Word& word) const
    {
        return checkGreenLetters(word) && checkYellowLetters(word) && checkGreyLetters(word);
    }
    LetterPos WordFilter::parseSinglePositionString(std::string& token) const
    {
        LetterPos lp;
        lp.letter = charToInt(token[0]);
        lp.position = static_cast<std::size_t>(intCharToNum(token[1])) - 1; // convert to 0-indexed
        return lp;
    }

    void WordFilter::updateWithGuess(const Word& guessedWord, const Word& realWord)
    {
        
        for (std::size_t i = 0; i < WORD_LENGTH; ++i)
        {
            Letter guessedLetter = guessedWord.getLetterAtPosition(i);
            Letter realLetter = realWord.getLetterAtPosition(i);
            if (guessedLetter == realLetter)
            {
                addGreenLetter(i, guessedLetter);
            }
            else if (realWord.getLetterCount(guessedLetter) > 0)
            {
                addYellowLetter(i, guessedLetter);
            }
            else
            {
                addGreyLetter(i, guessedLetter);
            }
        }
    }

    void WordFilter::parsePositionsFile(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open positions file: " + filename);
        }

        std::string line;
        enum class Section { NONE, GREEN, YELLOW, GREY } currentSection = Section::NONE;

        while (std::getline(file, line))
        {
            // Remove leading/trailing whitespace
            line.erase(0, line.find_first_not_of(" \t\r\n"));
            line.erase(line.find_last_not_of(" \t\r\n") + 1);

            // Skip empty lines
            if (line.empty())
            {
                continue;
            }

            // Check for section headers
            if (line == "green:")
            {
                currentSection = Section::GREEN;
                continue;
            }
            else if (line == "yellow:")
            {
                currentSection = Section::YELLOW;
                continue;
            }
            else if (line == "grey:")
            {
                currentSection = Section::GREY;
                continue;
            }

            // Parse letter-position pairs in the current section
            std::istringstream iss(line);
            std::string token;
            
            while (iss >> token)
            {
                if (token.length() >= 2)
                {
                    LetterPos lp = parseSinglePositionString(token);
                    
                    switch (currentSection)
                    {
                        case Section::GREEN:
                            addGreenLetter(lp.position, lp.letter);
                            break;
                        case Section::YELLOW:
                            addYellowLetter(lp.position, lp.letter);
                            break;
                        case Section::GREY:
                            addGreyLetter(lp.position, lp.letter);
                            break;
                        case Section::NONE:
                            // Ignore tokens before any section is defined
                            break;
                    }
                }
            }
        }
    }
}