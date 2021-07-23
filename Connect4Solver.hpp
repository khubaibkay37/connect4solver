#pragma once
#include <string>
#include "Position.hpp"
#include "TranspositionTable.hpp"

class Connect4Solver
{
private:
    int heuristic[7];
     TranspositionTable transTable;
public:
    Connect4Solver();
    void solve(const char *starting_position);
    void get_value(const char *starting_position);
    int negamax(const Position &P);
    int negamax_with_pruning(const Position &P, int alpha, int beta);
};
