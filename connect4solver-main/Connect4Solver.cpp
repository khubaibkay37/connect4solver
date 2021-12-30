#include "Connect4Solver.hpp"
#include "Position.hpp"
#include <iostream>
#include <cassert>

// See the score of a given position
// @param position: the position to evaluate

Connect4Solver::Connect4Solver() : transTable(8388593)
{
    for (int i = 0; i < Position::WIDTH; i++)
    {
        // Get to central element
        heuristic[i] = Position::WIDTH / 2;
        if (i % 2 == 0)
        {
            heuristic[i] += (i + 1) / 2;
        }
        else
        {
            heuristic[i] -= (i + 1) / 2;
        }
    }
}
void Connect4Solver::get_value(const char *position)
{
    Position pos;
    pos.play(position);
    int min = -(Position::WIDTH * Position::HEIGHT - pos.nbMoves()) / 2;
    int max = (Position::WIDTH * Position::HEIGHT + 1 - pos.nbMoves()) / 2;
    while (min < max)
    { // iteratively narrow the min-max exploration window
        int med = min + (max - min) / 2;
        if (med <= 0 && min / 2 < med)
            med = min / 2;
        else if (med >= 0 && max / 2 > med)
            med = max / 2;
        int r = negamax_with_pruning(pos, med, med + 1); // use a null depth window to know if the actual score is greater or smaller than med
        if (r <= med)
            max = r;
        else
            min = r;
    }
    std::cout << min << std::endl;
}

void Connect4Solver::non_loosing_moves()
{
}

// Prints the best posible move for a given position
// @param position: the position to evaluate
void Connect4Solver::solve(const char *position)
{
    // position you currently are at
    Position posMain;
    posMain.play(position);
    int bestpos = -1;
    int bestscore = -20000;
    for (int i = 0; i < Position::WIDTH; i++)
    {
        // Go column by column, you can even use heuristic
        if (posMain.canPlay(i))
        {
            int min = -(Position::WIDTH * Position::HEIGHT - posMain.nbMoves() - 1) / 2;
            // if the column isn't a winning move, calculate manually
            if (!posMain.isWinningMove(i))
            {
                Position pos(posMain);
                pos.play(i);
                int max = (Position::WIDTH * Position::HEIGHT + 1 - pos.nbMoves()) / 2;
                while (min < max)
                { // iteratively narrow the min-max exploration window
                    int med = min + (max - min) / 2;
                    if (med <= 0 && min / 2 < med)
                        med = min / 2;
                    else if (med >= 0 && max / 2 > med)
                        med = max / 2;
                    int r = negamax_with_pruning(pos, med, med + 1); // use a null depth window to know if the actual score is greater or smaller than med
                    if (r <= med)
                        max = r;
                    else
                        min = r;
                }
                if (bestscore < -min)
                {
                    bestscore = -min;
                    bestpos = i;
                }
            }
            else
            {
                bestscore = (Position::WIDTH * Position::HEIGHT + 1 - posMain.nbMoves() - 1) / 2;
                bestpos = i;
            }
        }
    }
    std::cout << bestpos + 1 << std::endl;
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
/*
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
    if (int val = transTable.get(P.key()))
    {
        max = val + Position::MIN_SCORE - 1;
    }
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
    for (int y = 0; y < Position::WIDTH; y++)
    {
        int x = heuristic[y];
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
    }                                                         // We return the best score we have seen so far.
    transTable.put(P.key(), alpha - Position::MIN_SCORE + 1); // save the upper bound of the position
    return alpha;
}
*/

int Connect4Solver::negamax_with_pruning(const Position &P, int alpha, int beta)
{
    // This is just to see if we didn't f- any thing up
    assert(alpha < beta);
    assert(!P.canWinNext());

    //check if there are any possible moves to play where you dont lose directly
    uint64_t next = P.possibleNnlosingMoves();

    if (next == 0) //if there are no non trivial moves to play
    {
        return -(Position::WIDTH * Position::HEIGHT - P.nbMoves()) / 2;
    }

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

    int min = -(Position::WIDTH * Position::HEIGHT - 2 - P.nbMoves()) / 2; // lower bound of score as opponent cannot win next move
    if (alpha < min)
    {
        alpha = min; // there is no need to keep beta above our max possible score.
        if (alpha >= beta)
        {
            return alpha; // prune the exploration if the [alpha;beta] window is empty.
        }
    }

    // We update beta value. [alpha,beta] is the range of values that the score could lie in.
    int max = (Position::WIDTH * Position::HEIGHT - 1 - P.nbMoves()) / 2;
    if (int val = transTable.get(P.key()))
    {
        max = val + Position::MIN_SCORE - 1;
    }
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
    for (int y = 0; y < Position::WIDTH; y++)
    {

        if (next & Position::column_mask(heuristic[y]))
        {
            Position P2(P);
            P2.play(heuristic[y]);                                // It's opponent turn in P2 position after current player plays x column.
            int score = -negamax_with_pruning(P2, -beta, -alpha); // explore opponent's score within [-beta;-alpha] windows:
            if (score >= beta)
            {
                return score;
            } // prune the exploration if we find a possible move better than what we were looking for.
            if (score > alpha)
            {
                alpha = score;
            } // reduce the [alpha;beta] window for next exploration, as we only
        }
        /*
        int x = heuristic[y]; 
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
        */
    }                                                         // We return the best score we have seen so far.
    transTable.put(P.key(), alpha - Position::MIN_SCORE + 1); // save the upper bound of the position
    return alpha;
}
