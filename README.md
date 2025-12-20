# Wordle C++ Solver

Attempt to find the best wordle word based on a simple idea:
the best word is the one that narrows down the list of remaining words the most.

## Building

```bash
g++ -std=c++17 -stdlib=libc++ -g main.cpp $(find src -type f -iregex ".*\.cpp") -o a
```

## Running

```bash
./a [positions_file]
```

If no positions file is provided, it defaults to `wordle_positions.txt`.

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
