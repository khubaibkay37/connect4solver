#include "Connect4Solver.hpp"
#include "Position.hpp"
#include <iostream>
#include <cassert>

// See the score of a given position
// @param position: the position to evaluate
void Connect4Solver::get_value(const char *position)
{
    Position pos;
    pos.play(position);
    std::cout << negamax_with_pruning(pos, -Position::WIDTH * Position::HEIGHT / 2, Position::WIDTH * Position::HEIGHT / 2) << std::endl;
    // std::cout << negamax(pos) << std::endl;
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
// ! DEPRECATED FUNCTION. THIS WILL NOT BE USED ANYMORE
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

// Gives the score of a position using alpha beta pruning
// @param P: the position to evaluate
// @param alpha: the alpha value, alpha is the best score we have seen for a maximizing player
// @param beta: the beta value, beta is the worst score we have seen for a maximizing player (best score for minimizing player)
int Connect4Solver::negamax_with_pruning(const Position &P, int alpha, int beta)
{
    // This is just to see if we didn't f- any thing up
    assert(alpha < beta);
    // If game is a draw
    if (P.nbMoves() == Position::WIDTH * Position::HEIGHT)
        return 0;

    // See if current player can win next move
    for (int x = 0; x < Position::WIDTH; x++)
    {
        if (P.canPlay(x) && P.isWinningMove(x))
        {
            return (Position::WIDTH * Position::HEIGHT + 1 - P.nbMoves()) / 2;
        }
    }
    // We update beta value. [alpha,beta] is the range of values that the score could lie in.
    int max = (Position::WIDTH * Position::HEIGHT - 1 - P.nbMoves()) / 2;
    if (beta > max)
    {
        beta = max;
        // Since we changed the window, see if [alpha,beta] is empty or not, if it is then return beta 
        // since it is max score we can get
        if (alpha >= beta)
        {
            return beta;
        }
    }
    // Go over possible moves
    for (int x = 0; x < Position::WIDTH; x++)
        if (P.canPlay(x))
        {
            // We are the maximizing player
            Position P2(P);
            // It's opponent turn in P2 position after current player plays x column.
            P2.play(x);
            // Negamax assumes the next move is by maximizing player, hence we add a minus sign, to get score for us.
            // Our opponent's best score seen so far is our worst, and opponent's worst score is so far our best
            // hence -beta is alpha for opponent, and -alpha is beta for the opponent.
            int score = -negamax_with_pruning(P2, -beta, -alpha);
            // If we do better than what the opponent has seen so far, the opponent won't go this path
            // and hence we can prune the rest of the tree.
            if (score >= beta)
            {
                return score;
            }
            // if we see a better score for ourselves, we update alpha value
            if (score > alpha)
            {
                alpha = score;
            }
        }
    // We return the best score we have seen so far.
    return alpha;
}
