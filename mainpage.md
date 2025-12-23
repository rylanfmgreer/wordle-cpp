# Wordle C++ Solver Documentation

@mainpage Wordle C++ Solver

@section intro_sec Introduction

This is an optimal Wordle solver written in C++ that finds the best word to guess by minimizing the expected number of remaining candidates. The solver features fancy terminal output with ASCII art and color-coded results.

@section features_sec Key Features

- **Optimal Word Selection**: Uses a minimax-style algorithm to find guesses that eliminate the most words on average
- **Position Filtering**: Supports constraint files specifying known letter positions
- **Fancy Output**: Colorful terminal displays with ASCII art and emoji 🐸
- **Backtesting**: Comprehensive performance testing against all possible target words
- **Well-Documented**: Full Doxygen documentation for all components

@section structure_sec Project Structure

The codebase is organized into several modules:

### Core Modules

- **board/** - Game board simulation and constraint tracking (Wordle::BoardWithKnownAnswer)
- **word/** - Word representation, filtering, and loading (Wordle::Word, Wordle::WordFilter)
- **runner/** - Main solvers and backtesting utilities (Wordle::getBestWord, Wordle::backtest)
- **printing_utils/** - Terminal output formatting and ASCII art display
- **utils/** - Helper functions for character conversion

@section usage_sec Basic Usage

@subsection compilation Compilation

```bash
g++ -std=c++17 -stdlib=libc++ -g main.cpp $(find src -type f -iregex ".*\.cpp") -o a
```

@subsection running Running

```bash
./a [positions_file]
```

If no positions file is provided, defaults to `wordle_positions.txt`.

@subsection filter_format Position Filter Format

The position filter file specifies known information:

```
green:
L1 E2 T3

yellow:
A4

grey:
R1 S2
```

- **green**: Letter in correct position (letter + 1-indexed position)
- **yellow**: Letter in word but wrong position
- **grey**: Letter not in the word

@section algorithm_sec Algorithm

The solver works as follows:

1. For each candidate guess word:
   - Simulate guessing it against every possible target
   - Count remaining candidates after each simulation
   - Calculate average remaining words

2. Select the word with the lowest average

3. Apply position filters to narrow search space

This approach finds optimal first guesses like "raise", "slate", or "crate".

@section classes_sec Key Classes

- Wordle::Word - Represents a 5-letter word with efficient letter lookup
- Wordle::WordFilter - Filters words based on Wordle feedback (green/yellow/grey)
- Wordle::BoardWithKnownAnswer - Simulates game board with constraint tracking
- Wordle::WordResult - Contains best word with statistics

@section functions_sec Main Functions

- Wordle::getBestWord() - Find optimal word given constraints
- Wordle::dailyRun() - User-facing solver with fancy output
- Wordle::backtest() - Test performance on specific target word
- Wordle::backtestAllWords() - Comprehensive performance evaluation

@section performance_sec Performance

The solver typically achieves:
- 3-4 guesses average on standard Wordle word list
- Sub-second computation for first guess
- Efficient constraint propagation for subsequent guesses

@section author_sec Author

Rylan Greer

@section license_sec License

[Add license information]
