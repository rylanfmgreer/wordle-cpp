/**
 * @file gui_demo.cpp
 * @brief Demo program for the terminal GUI
 */

#include "src/gui/terminal_gui.hpp"
#include <iostream>

int main()
{
    std::cout << "Starting Wordle Terminal GUI...\n";
    std::cout << "Press any key to begin...\n";
    std::cin.get();
    
    bool success = Wordle::launchTerminalGUI("wordle_positions.txt");
    
    if (success)
    {
        std::cout << "\nYou can now run the solver with:\n";
        std::cout << "  ./a wordle_positions.txt\n";
    }
    
    return 0;
}
