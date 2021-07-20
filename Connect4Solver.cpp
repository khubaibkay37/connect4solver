#include "Connect4Solver.hpp"
#include "Position.hpp"
#include <iostream>

// See the score of a given position
// @param position: the position to evaluate
void Connect4Solver::get_value(const char *position)
{
    Position pos;
    pos.play(position);
    std::cout << negamax(pos) << std::endl;
}

// Prints the best posible move for a given position
// @param position: the position to evaluate
void Connect4Solver::solve(const char *position)
{
    Position pos;
    pos.play(position);
    int bestmove = -1;
    int bestscore = -1000;
    for (int i = 0; i < 7; i++)
    {
        if (pos.canPlay(i))
        {
            Position test(pos);
            test.play(i);
            // See value for us
            int score = -negamax(pos);
            if (score > bestscore)
            {
                bestscore = score;
                bestmove = i;
            }
        }
    }
    std::cout << bestmove + 1 << std::endl;
}

int Connect4Solver::negamax(const Position &P)
{
    if (P.nbMoves() == Position::WIDTH * Position::HEIGHT) // check for draw game
        return 0;

    for (int x = 0; x < Position::WIDTH; x++) // check if current player can win next move
        if (P.canPlay(x) && P.isWinningMove(x))
            return (Position::WIDTH * Position::HEIGHT + 1 - P.nbMoves()) / 2;

    int bestScore = -Position::WIDTH * Position::HEIGHT; // init the best possible score with a lower bound of score.

    for (int x = 0; x < Position::WIDTH; x++) // compute the score of all possible next move and keep the best one
        if (P.canPlay(x))
        {
            Position P2(P);
            P2.play(x);               // It's opponent turn in P2 position after current player plays x column.
            int score = -negamax(P2); // If current player plays col x, his score will be the opposite of opponent's score after playing col x
            if (score > bestScore)
                bestScore = score; // keep track of best possible score so far.
        }

    return bestScore;
}
