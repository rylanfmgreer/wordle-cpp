#include <iostream>
#include "src/get_best_word.hpp"

int main()
{
    Wordle::Word best_word = Wordle::get_best_word();
    std::cout << "Best word: " << best_word.get_base_word() << std::endl;
    return 0;
}
