/**
 * @file gui_demo.cpp
 * @brief Demo program for the terminal GUI
 */

#include "src/gui/terminal_gui.hpp"
#include <iostream>
#include "src/printing_utils/print_functions.hpp"
int main()
{

    Wordle::standardInitialPrints();
    std::cout << "\n  Starting Wordle Terminal GUI...\n";
    std::cout << "  Press " << Wordle::BOLD << "ENTER" << Wordle::RESET << " to begin...\n";
    std::cin.get();
    
    bool success = Wordle::launchTerminalGUI("wordle_positions.txt");
    
    if (success)
    {
        std::cout << "\nYou can now run the solver with:\n";
        std::cout << "  ./a wordle_solver\n";
    }
    
    return 0;
}
