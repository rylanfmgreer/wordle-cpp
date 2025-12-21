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
} // namespace Wordle
