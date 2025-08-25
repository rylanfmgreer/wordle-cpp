Attempt to find the best wordle word based on a simple idea:
the best word is the one that narrows down the list of remainign words the most

g++ -std=c++17  -stdlib=libc++  -g main.cpp  $(find src -type f -iregex ".*\.cpp") -o a
