all: ; g++ src/lexicon.cpp src/token.cpp src/scanner.cpp src/treeNode.cpp src/tree.cpp src/parser.cpp main.cpp -o rpal -std=c++11
cl: ; rm -f *.o rpal