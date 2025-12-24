#include "create_word_list.hpp"
#include <fstream>
#include <sstream>

namespace Wordle
{
    std::vector<Word> createWordList(const std::string& p_filename)

    {
        std::vector<Word> word_list;
        std::ifstream file(p_filename);
        std::string line;

        while (std::getline(file, line))
        {
            Word word(line);
            word_list.push_back(word);
        }
        file.close();
        return word_list;
    }
}
