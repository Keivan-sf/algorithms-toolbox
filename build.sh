rm -rf main
g++ -c main.cpp infix_parser.cpp
g++ main.o infix_parser.o -o main
rm -rf main.o infix_parser.o
./main
