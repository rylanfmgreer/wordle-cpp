/**
 * @file terminal_gui.cpp
 * @brief Implementation of terminal-based GUI for Wordle input
 * @author Rylan Greer
 */

#include "terminal_gui.hpp"
#include "../runner/get_best_word.hpp"
#include <iostream>
#include <fstream>
#include <cctype>
#include <termios.h>
#include <unistd.h>

namespace Wordle
{
    // ANSI color codes
    const std::string COLOR_GREEN = "\033[42m\033[30m";   // Green background, black text
    const std::string COLOR_YELLOW = "\033[43m\033[30m";  // Yellow background, black text
    const std::string COLOR_GREY = "\033[100m\033[37m";   // Grey background, white text
    const std::string COLOR_UNKNOWN = "\033[47m\033[30m"; // White background, black text
    const std::string COLOR_CURSOR = "\033[7m";           // Inverse colors
    const std::string COLOR_RESET = "\033[0m";
    const std::string BOLD = "\033[1m";

    TerminalGUI::TerminalGUI() : currentRow_(0), currentPosition_(0), lastSuggestion_("")
    {
        rows_.resize(1);  // Start with one row
    }

    std::string TerminalGUI::getColorCode(LetterStatus status) const
    {
        switch (status)
        {
            case LetterStatus::GREEN:
                return COLOR_GREEN;
            case LetterStatus::YELLOW:
                return COLOR_YELLOW;
            case LetterStatus::GREY:
                return COLOR_GREY;
            default:
                return COLOR_UNKNOWN;
        }
    }

    void TerminalGUI::displayLetterBox(const LetterInput& input, bool isCurrent) const
    {
        std::string colorCode = getColorCode(input.status);
        std::string cursor = isCurrent ? COLOR_CURSOR : "";
        
        char displayChar = (input.letter == ' ') ? '_' : std::toupper(input.letter);
        
        std::cout << cursor << colorCode << " " << displayChar << " " << COLOR_RESET;
    }

    void TerminalGUI::displayHelp() const
    {
        std::cout << "\n" << BOLD << "Controls:" << COLOR_RESET << "\n";
        std::cout << "  Type letters (a-z) to enter\n";
        std::cout << "  Left/Right arrows to move between letters\n";
        std::cout << "  Up/Down arrows to move between rows\n";
        std::cout << "  " << COLOR_GREEN << "1" << COLOR_RESET << " = Green (correct position)\n";
        std::cout << "  " << COLOR_YELLOW << "2" << COLOR_RESET << " = Yellow (wrong position)\n";
        std::cout << "  " << COLOR_GREY << "3" << COLOR_RESET << " or Space = Grey (not in word)\n";
        std::cout << "  " << BOLD << "4" << COLOR_RESET << " = Add new row (max 6 rows)\n";
        std::cout << "  " << BOLD << "5" << COLOR_RESET << " = Run solver for suggestion\n";
        std::cout << "  Backspace = Clear letter\n";
        std::cout << "  Enter = Confirm and save\n";
        std::cout << "  6 = Quit without saving\n";
        std::cout << "\n" << BOLD << "Tip:" << COLOR_RESET << " Enter letters first, then mark colors!\n";
    }

    void TerminalGUI::display() const
    {
        // Clear screen
        std::cout << "\033[2J\033[H";
        
        std::cout << BOLD << "\n🐸 Wordle Letter Input (Row " << (currentRow_ + 1) << "/" << rows_.size() << ")" << COLOR_RESET << "\n\n";
        
        // Display all rows
        for (size_t row = 0; row < rows_.size(); ++row)
        {
            std::cout << "  ";
            for (int i = 0; i < 5; ++i)
            {
                bool isCurrent = (row == currentRow_ && i == currentPosition_);
                displayLetterBox(rows_[row].letters[i], isCurrent);
                std::cout << " ";
            }
            if (row == currentRow_)
            {
                std::cout << " ← Current row";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
        
        // Display last solver suggestion if available
        if (!lastSuggestion_.empty())
        {
            std::cout << BOLD << "💡 Suggested word: " << COLOR_RESET << lastSuggestion_ << "\n";
        }
        
        displayHelp();
        
        std::cout << "\nCurrent: Row " << (currentRow_ + 1) << ", Position " << (currentPosition_ + 1);
        if (rows_[currentRow_].letters[currentPosition_].letter != ' ')
        {
            std::cout << ", Letter '" << char(std::toupper(rows_[currentRow_].letters[currentPosition_].letter)) << "'";
        }
        std::cout << "\n";
    }

    char getch()
    {
        char buf = 0;
        struct termios old = {0};
        fflush(stdout);
        if (tcgetattr(0, &old) < 0)
            perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
            perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
            perror("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
            perror("tcsetattr ~ICANON");
        return buf;
    }

    bool TerminalGUI::handleInput()
    {
        char ch = getch();
        
        // Handle arrow keys (escape sequences)
        if (ch == 27)
        {
            getch(); // Skip '['
            ch = getch();
            if (ch == 'C' || ch == '6') // Right arrow
            {
                currentPosition_ = (currentPosition_ + 1) % 5;
            }
            else if (ch == 'D' || ch == '4') // Left arrow
            {
                currentPosition_ = (currentPosition_ - 1 + 5) % 5;
            }
            else if (ch == 'A' || ch == '2') // Up arrow
            {
                if (currentRow_ > 0)
                {
                    currentRow_--;
                }
            }
            else if (ch == 'B' || ch == '5') // Down arrow
            {
                if (currentRow_ < static_cast<int>(rows_.size()) - 1)
                {
                    currentRow_++;
                }
            }
            return true;
        }
        
        char chLower = std::tolower(ch);
        
        // Handle color selection with numbers
        if (ch == '1')
        {
            rows_[currentRow_].letters[currentPosition_].status = LetterStatus::GREEN;
            currentPosition_ = (currentPosition_ + 1) % 5;
            return true;
        }
        if (ch == '2')
        {
            rows_[currentRow_].letters[currentPosition_].status = LetterStatus::YELLOW;
            currentPosition_ = (currentPosition_ + 1) % 5;
            return true;
        }
        if (ch == '3' || ch == ' ')
        {
            rows_[currentRow_].letters[currentPosition_].status = LetterStatus::GREY;
            currentPosition_ = (currentPosition_ + 1) % 5;
            return true;
        }
        
        // Add new row
        if (ch == '4')
        {
            if (addNewRow())
            {
                currentPosition_ = 0;
            }
            return true;
        }
        
        // Run solver
        if (ch == '5')
        {
            runSolver();
            return true;
        }
        
        // Handle letter input (case insensitive)
        if (chLower >= 'a' && chLower <= 'z' && chLower != 'q')
        {
            rows_[currentRow_].letters[currentPosition_].letter = chLower;
            return true;
        }
        
        // Handle backspace/delete
        if (ch == 127 || ch == 8)
        {
            rows_[currentRow_].letters[currentPosition_].letter = ' ';
            rows_[currentRow_].letters[currentPosition_].status = LetterStatus::UNKNOWN;
            return true;
        }
        
        // Handle enter (confirm)
        if (ch == '\n' || ch == '\r')
        {
            return false; // Exit loop, confirmed
        }
        
        // Handle quit
        if (ch == '6')
        {
            return false; // Exit loop, cancelled
        }
        
        return true;
    }

    bool TerminalGUI::run()
    {
        while (true)
        {
            display();
            if (!handleInput())
            {
                break;
            }
        }
        
        // Check if user actually entered something
        bool hasInput = false;
        for (const auto& row : rows_)
        {
            for (const auto& letter : row.letters)
            {
                if (letter.letter != ' ')
                {
                    hasInput = true;
                    break;
                }
            }
            if (hasInput) break;
        }
        
        return hasInput;
    }

    bool TerminalGUI::addNewRow()
    {
        if (rows_.size() >= 6)
        {
            return false;  // Max 6 rows
        }
        rows_.push_back(WordRow());
        currentRow_ = rows_.size() - 1;
        return true;
    }

    void TerminalGUI::runSolver()
    {
        // Clear screen for solver output
        std::cout << "\033[2J\033[H";
        
        // Save current state to temp file
        std::string tempFile = "/tmp/wordle_gui_temp.txt";
        saveToFile(tempFile);
        
        // Run solver
        std::cout << "\n" << BOLD << "🔍 Running solver..." << COLOR_RESET << "\n\n";
        try
        {
            WordResult result = getBestWord(tempFile, true, false);
            lastSuggestion_ = result.word.getBaseWord();
            std::cout << BOLD << "✅ Best word: " << COLOR_RESET << BOLD << lastSuggestion_ << COLOR_RESET << "\n";
            std::cout << "   Average knockout: " << result.averageKnockout << "\n";
            std::cout << "\n" << BOLD << "Press ENTER to return to GUI..." << COLOR_RESET;
            std::cout.flush();
            getch();
        }
        catch (const std::exception& e)
        {
            std::cout << "❌ Error running solver: " << e.what() << "\n";
            std::cout << "\n" << BOLD << "Press ENTER to return to GUI..." << COLOR_RESET;
            std::cout.flush();
            getch();
        }
    }

    std::vector<std::pair<char, int>> TerminalGUI::getGreenLetters() const
    {
        std::vector<std::pair<char, int>> result;
        for (const auto& row : rows_)
        {
            for (const auto& input : row.letters)
            {
                if (input.status == LetterStatus::GREEN && input.letter != ' ')
                {
                    result.push_back({input.letter, input.position + 1});
                }
            }
        }
        return result;
    }

    std::vector<std::pair<char, int>> TerminalGUI::getYellowLetters() const
    {
        std::vector<std::pair<char, int>> result;
        for (const auto& row : rows_)
        {
            for (const auto& input : row.letters)
            {
                if (input.status == LetterStatus::YELLOW && input.letter != ' ')
                {
                    result.push_back({input.letter, input.position + 1});
                }
            }
        }
        return result;
    }

    std::vector<std::pair<char, int>> TerminalGUI::getGreyLetters() const
    {
        std::vector<std::pair<char, int>> result;
        for (const auto& row : rows_)
        {
            for (const auto& input : row.letters)
            {
                if (input.status == LetterStatus::GREY && input.letter != ' ')
                {
                    result.push_back({input.letter, input.position + 1});
                }
            }
        }
        return result;
    }

    void TerminalGUI::saveToFile(const std::string& filename) const
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Error: Could not open file " << filename << " for writing.\n";
            return;
        }

        // Write green letters
        file << "green:\n";
        auto greenLetters = getGreenLetters();
        for (const auto& pair : greenLetters)
        {
            file << pair.first << pair.second;
            if (&pair != &greenLetters.back())
                file << " ";
        }
        file << "\n\n";

        // Write yellow letters
        file << "yellow:\n";
        auto yellowLetters = getYellowLetters();
        for (const auto& pair : yellowLetters)
        {
            file << pair.first << pair.second;
            if (&pair != &yellowLetters.back())
                file << " ";
        }
        file << "\n\n";

        // Write grey letters
        file << "grey:\n";
        auto greyLetters = getGreyLetters();
        for (const auto& pair : greyLetters)
        {
            file << pair.first << pair.second;
            if (&pair != &greyLetters.back())
                file << " ";
        }
        file << "\n";

        file.close();
        file.flush();  // Ensure file is written to disk
        std::cout << "\nSaved to " << filename << "\n";
    }

    bool launchTerminalGUI(const std::string& outputFilename)
    {
        TerminalGUI gui;
        bool completed = gui.run();
        
        if (completed)
        {
            gui.saveToFile(outputFilename);
            std::cout << "\n✅ Input saved successfully!\n";
            return true;
        }
        else
        {
            std::cout << "\n❌ Input cancelled.\n";
            return false;
        }
    }
}
