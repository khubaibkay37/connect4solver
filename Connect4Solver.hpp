#pragma once
#include <string>
#include "Position.hpp"

class Connect4Solver
{

public:
    static void solve(const char* starting_position);
    static void get_value(const char* starting_position);
    static int negamax(const Position &P);
    static int negamax_with_pruning(const Position &P,int alpha, int beta);
};

