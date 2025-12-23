#!/bin/bash
# Build script for Wordle C++ Solver

echo "🐸 Building Wordle C++ Solver..."

# Build main solver
echo "Building main solver..."
g++ -std=c++17 -stdlib=libc++ -g main.cpp $(find src -type f -iregex ".*\.cpp") -o wordle_solver

if [ $? -eq 0 ]; then
    echo "✅ Main solver built successfully -> ./wordle_solver"
else
    echo "❌ Failed to build main solver"
    exit 1
fi

# Build GUI demo
echo "Building GUI demo..."
g++ -std=c++17 -stdlib=libc++ -g gui_demo.cpp \
    src/gui/terminal_gui.cpp \
    src/runner/get_best_word.cpp \
    src/word/word.cpp \
    src/word/create_word_list.cpp \
    src/board/board.cpp \
    src/utils/utils.cpp \
    src/filter/filter.cpp \
    src/printing_utils/print_functions.cpp \
    -o solver

if [ $? -eq 0 ]; then
    echo "✅ GUI demo built successfully -> ./solver"
else
    echo "❌ Failed to build GUI demo"
    exit 1
fi

echo ""
echo "🎉 Build complete!"
echo ""
echo "To use:"
echo "  1. Run the GUI to input letters:  ./solver"
echo "  2. Run the solver:                ./wordle_solver"
echo ""
