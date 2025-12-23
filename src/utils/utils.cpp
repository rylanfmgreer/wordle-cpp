#include "utils.hpp"
#include <algorithm>
#include <cctype>
namespace Wordle
{
    std::string toLowerCase(const std::string& str)
    {
        std::string lower_str = str;
        std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return lower_str;
    }

    int countDistinctVowels(const std::string& word)
    {
        std::string vowels = "aeiou";
        int count = 0;
        for (char v : vowels)
        {
            if (word.find(v) != std::string::npos)
                count++;
        }
        return count;
    }
    bool hasDoubleLetters(const std::string& word)
    {
        Letter letterSeen[26];
        std::fill_n(letterSeen, 26, 0);
        for(int i = 0; i < word.length(); ++i)
        {
            Letter l = charToInt(word[i]);
            letterSeen[l]++;
            if(letterSeen[l] > 1)
                return true;
        }
        return false;
    }

} // namespace Wordle
