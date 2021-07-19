#include <iostream>
// include time
// include cstring
#include <cstring>
#include <ctime>
#include "Connect4Solver.hpp"
int main(int argc, char const *argv[])
{
    // std::cout << "Hello World!" << std::endl;

    // // for loop printing all elements in argv
    // for (int i = 0; i < argc; i++)
    // {
    //     std::cout << argv[i] << std::endl;
    // }
    // Generate a random number and print it
    // initialize seed
    if (argc != 3)
    {
        std::cout << "Usage: ./Connect4Solver <value/best> starting_position" << std::endl;
        return 1;
    }
    if (strcmp(argv[1], "value") == 0) {
    Connect4Solver::getvalue(argv[2]);
    }
    else {
        Connect4Solver::solve(argv[2]);
    }
    // std::srand(std::time(0));
    //     std::cout << std::rand() % 100 + 1<< std::endl;
    return 0;
}