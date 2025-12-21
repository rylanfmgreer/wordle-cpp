# Wordle C++ Solver 🐸

An optimal Wordle solver that finds the best word to guess based on minimizing the expected number of remaining candidates. Features fancy terminal output with ASCII art and color-coded results!

## Features

- **Optimal word selection**: Analyzes all possible guesses to find the one that eliminates the most words on average
- **Position filtering**: Supports input files specifying known letter positions (green/yellow/grey)
- **Fancy terminal output**: Colorful ASCII art displays with frog emoji 🐸
- **Backtesting suite**: Test solver performance against all possible target words
- **Comprehensive API documentation**: Full Doxygen documentation for all components

## Project Structure

```
wordle-cpp/
├── src/
│   ├── board/          # Game board simulation and constraint tracking
│   ├── word/           # Word representation and filtering
│   ├── runner/         # Main solvers and backtesting
│   ├── printing_utils/ # Fancy terminal output functions
│   └── utils/          # Helper utilities
├── main.cpp            # Entry point
└── wordle_positions.txt # Example position filter file
```

## Building

```bash
g++ -std=c++17 -stdlib=libc++ -g main.cpp $(find src -type f -iregex ".*\.cpp") -o a
```

## Running

### Basic Usage

```bash
./a [positions_file]
```

If no positions file is provided, it defaults to `wordle_positions.txt`.

### Position Filter File Format

The position filter file specifies known information about letter positions:

```
green:
L1 E2 T3

yellow:
A4

grey:
R1 S2
```

- **green**: Letters in correct positions (letter + position)
- **yellow**: Letters in the word but wrong position
- **grey**: Letters not in the word

## How It Works

The solver uses a minimax-style algorithm:

1. **For each possible guess word**:
   - Simulate guessing it against every possible target word
   - Count how many candidates would remain after each simulation
   - Calculate the average number of remaining words

2. **Select the word** that results in the fewest remaining candidates on average

3. **Apply position filters** if provided to narrow down the search space

## Core Components

### Word Representation (`src/word/`)
- `Word`: Efficient letter storage and frequency counting
- `WordFilter`: Filters words based on Wordle feedback
- `createWordList()`: Loads word lists from files

### Board Simulation (`src/board/`)
- `BoardWithKnownAnswer`: Tracks constraints and validates potential solutions
- Maintains min/max letter counts and position possibilities

### Solvers (`src/runner/`)
- `getBestWord()`: Main solver function
- `backtest()`: Performance testing against specific words
- `backtestAllWords()`: Comprehensive performance evaluation
- `dailyRun()`: User-facing solver with fancy output

### Printing (`src/printing_utils/`)
- ASCII art rendering
- Color-coded terminal output
- Animated displays
- Progress indicators

## Documentation

This project uses Doxygen for API documentation. All header files are documented with Doxygen-style comments.

### Generating Documentation

1. Install Doxygen (and optionally Graphviz for diagrams):
   ```bash
   # macOS
   brew install doxygen graphviz
   
   # Ubuntu/Debian
   sudo apt-get install doxygen graphviz
   ```

2. Generate the documentation:
   ```bash
   doxygen Doxyfile
   ```

3. View the documentation:
   ```bash
   open docs/html/index.html
   ```

The generated documentation will be in the `docs/html` directory.

## Example Output

```
  ╔════════════════════════════════╗
  ║     🐸 BEST WORDLE GUESS 🐸    ║
  ╠════════════════════════════════╣
  ║          raise          ║
  ╚════════════════════════════════╝

  raise knocks out 61 words on average
  Remaining possible words: 2309
```

## Algorithm Performance

The solver typically finds optimal first guesses like "raise", "slate", or "crate" depending on the word list. With proper filtering after each guess, it can solve most Wordles in 3-4 guesses.

## Contributing

Feel free to contribute improvements! Areas for enhancement:
- Optimizations for faster word evaluation
- Additional output formats
- Interactive mode
- Word list management

## Author

Rylan Greer

## License

[Add your license here]

