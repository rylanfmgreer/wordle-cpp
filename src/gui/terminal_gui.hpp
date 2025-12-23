/**
 * @file terminal_gui.hpp
 * @brief Terminal-based GUI for inputting Wordle letter positions
 * @author Rylan Greer
 */

#ifndef TERMINAL_GUI_HPP
#define TERMINAL_GUI_HPP

#include <string>
#include <vector>
#include "../datatypes.hpp"

namespace Wordle
{
    /**
     * @enum LetterStatus
     * @brief Status of a letter in Wordle (matches color codes)
     */
    enum class LetterStatus
    {
        UNKNOWN,  ///< Not yet set
        GREEN,    ///< Correct letter, correct position
        YELLOW,   ///< Correct letter, wrong position
        GREY      ///< Letter not in word
    };

    /**
     * @struct LetterInput
     * @brief Represents a single letter input with its status
     */
    struct LetterInput
    {
        char letter;           ///< The letter (a-z, or ' ' for empty)
        LetterStatus status;   ///< The status (green/yellow/grey)
        int position;          ///< Position in word (0-4)
    };

    /**
     * @struct WordRow
     * @brief Represents one complete row of 5 letters
     */
    struct WordRow
    {
        std::vector<LetterInput> letters;  ///< The 5 letters in this row
        
        WordRow() : letters(5) 
        {
            for (int i = 0; i < 5; ++i)
            {
                letters[i].letter = ' ';
                letters[i].status = LetterStatus::UNKNOWN;
                letters[i].position = i;
            }
        }
    };

    /**
     * @class TerminalGUI
     * @brief Interactive terminal GUI for entering Wordle guesses
     * 
     * Displays a 5-letter word grid where users can:
     * - Type letters (a-z)
     * - Press 1 for green, 2 for yellow, 3 for grey
     * - Navigate with arrow keys
     * - Press 4 to add new row (up to 6 rows)
     * - Press 5 to run solver and get suggestion
     * - Export to position filter file format
     */
    class TerminalGUI
    {
    public:
        /**
         * @brief Constructor initializes empty grid
         */
        TerminalGUI();

        /**
         * @brief Run the interactive GUI loop
         * @return true if user confirmed input, false if cancelled
         */
        bool run();

        /**
         * @brief Get all green letters from all rows
         * @return Vector of letter/position pairs
         */
        std::vector<std::pair<char, int>> getGreenLetters() const;

        /**
         * @brief Get all yellow letters from all rows
         * @return Vector of letter/position pairs
         */
        std::vector<std::pair<char, int>> getYellowLetters() const;

        /**
         * @brief Get all grey letters from all rows
         * @return Vector of letter/position pairs
         */
        std::vector<std::pair<char, int>> getGreyLetters() const;

        /**
         * @brief Save input to position filter file
         * @param filename File to save to
         */
        void saveToFile(const std::string& filename) const;

        /**
         * @brief Display the current state
         */
        void display() const;

    private:
        std::vector<WordRow> rows_;          ///< All word rows (up to 6)
        int currentRow_;                     ///< Current row being edited
        int currentPosition_;                ///< Current cursor position (0-4)
        std::string lastSuggestion_;         ///< Last solver suggestion

        /**
         * @brief Display a single letter box
         * @param input The letter to display
         * @param isCurrent Whether this is the current cursor position
         */
        void displayLetterBox(const LetterInput& input, bool isCurrent) const;

        /**
         * @brief Get color code for letter status
         * @param status The status
         * @return ANSI color code string
         */
        std::string getColorCode(LetterStatus status) const;

        /**
         * @brief Display help text
         */
        void displayHelp() const;

        /**
         * @brief Handle keyboard input
         * @return true to continue, false to exit
         */
        bool handleInput();

        /**
         * @brief Run the solver and get best word suggestion
         */
        void runSolver();

        /**
         * @brief Add a new row (up to 6 total)
         * @return true if row was added, false if at max
         */
        bool addNewRow();
    };

    /**
     * @brief Launch the terminal GUI and optionally save results
     * @param outputFilename File to save results to (optional)
     * @return true if user completed input, false if cancelled
     */
    bool launchTerminalGUI(const std::string& outputFilename = "wordle_positions.txt");
}

#endif // TERMINAL_GUI_HPP
