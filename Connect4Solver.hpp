#pragma once
#include <string>
#include "Position.hpp"

class Connect4Solver
{
private:
    /* data */
public:
    static void solve(const char* starting_position);
    static void getvalue(const char* starting_position);
    
    static int negamax(const Position &P);

    // Connect4Solver(char* starting_position);
    // ~Connect4Solver();
};

