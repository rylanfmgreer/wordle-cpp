
#include "print_functions.hpp"
using namespace Wordle;
int printAssetFromFilename(const std::string& filename, const std::string& prefix)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return 0;
    }

    std::string line;
    std::cout << prefix;
    int n_chars = 0;
    while (std::getline(file, line))
    {
        n_chars += line.size();
        std::cout <<prefix <<  line << "\n";
    }
    std::cout << RESET;

    file.close();
    return n_chars;
}

void backspacePrint(int n)
{
    for (int i = 0; i < n; ++i)
    {
        std::cout << "\b \b";
    }
}
void blinkAssetNTimes(const std::string& filename, int n_times, int delay_ms, const std::string& prefix)
{
    for (int i = 0; i < n_times; ++i)
    {
        int n_chars = printAssetFromFilename(filename, prefix);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        backspacePrint(n_chars);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
}   

std::string generateBestWordPrintStr(const Wordle::Word& best_word)
{
    std::string output;
    std::string emoji = getEmojiFromConfigValue("src/printing_utils/assets/emoji_config.txt");
    std::string title_bar = generateTitleBar(emoji);
    output += "\n";
    output += TOP_BAR + "\n";
    output += title_bar + "\n";
    output += MID_BAR + "\n";
    output += BAR_FORMAT + "  ║" + RESET + "             " + BOLD + GREEN + MAGENTA + best_word.getBaseWord() + RESET + "              " + BAR_FORMAT + "║" + RESET + "\n";
    output += BOT_BAR + "\n";
    output += "\n";
    return output;
}

std::string generateTitleBar(const std::string& emoji)
{
    return BAR_FORMAT + "  ║"  "     " + BOLD + BLACK + emoji + " BEST WORDLE GUESS " + emoji + RESET + "    " + BAR_FORMAT + "║" + RESET;
}

void printBestWord(const Wordle::Word& best_word)
{
    std::string output = generateBestWordPrintStr(best_word);
    std::cout << output;
}

int printNumberOfWordsKnockedOut(const std::string& word, LongInt n_remaining_words, LongInt n_words_knocked_out)
{

    std::string output_1 = "  Of the remaining " + BOLD + GREEN + std::to_string(n_remaining_words) +RESET+ " possible words,\n";
    std::string output ="  " +  BOLD + MAGENTA + word + RESET + " knocks out " + BOLD + MAGENTA + std::to_string(n_words_knocked_out) + RESET + " words on average\n";
    std::cout << output_1 << output;
    return output_1.size() + output.size();
}

std::string getEmojiFromConfigValue(const std::string& config_filepath)
{
    std::ifstream config_file(config_filepath);
    if (!config_file.is_open())
    {
        std::cerr << "Error: Could not open config file " << config_filepath << "\n";
        return "🐸"; // default emoji
    }

    std::string line;
    while (std::getline(config_file, line))
    {
        std::size_t delimiter_pos = line.find('=');
        if (delimiter_pos != std::string::npos)
        {
            std::string key = line.substr(0, delimiter_pos);
            std::string value = line.substr(delimiter_pos + 1);
            if (key == "emoji")
            {
                config_file.close();
                return value;
            }
        }
    }

    config_file.close();
    return "🐸"; // default emoji if not found
}
void standardInialPrints()
{
    printAssetFromFilename("src/printing_utils/assets/title_asset.txt", BOLD);
    printAssetFromFilename("src/printing_utils/assets/copyright_info.txt", RESET);
}