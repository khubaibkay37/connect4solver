#include <iostream>
// include time
// include cstring
#include <cstring>
#include <ctime>
#include "Connect4Solver.hpp"
int main(int argc, char const *argv[])
{
    Connect4Solver solver;
    if (argc != 3)
    {
        std::cout << "Usage: ./Connect4Solver <value/best> starting_position" << std::endl;
        return 1;
    }
    // See mode specified
    if (strcmp(argv[1], "value") == 0) {
    solver.get_value(argv[2]);
    }
    else if (strcmp(argv[1], "best") == 0){
        solver.solve(argv[2]);
    }
    else {
        std::cout << "Usage: ./Connect4Solver <value/best> starting_position" << std::endl;
        return 1;
    }
    return 0;
}