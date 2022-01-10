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
  void non_loosing_moves();
};

/*
   * This class helps sorting the next moves
   *
   * You have to add moves first with their score 
   * then you can get them back in decreasing score
   *
   * This class implement an insertion sort that is in practice very
   * efficient for small number of move to sort (max is Position::WIDTH)
   * and also efficient if the move are pushed in approximatively increasing 
   * order which can be acheived by using a simpler column ordering heuristic.
*/
class MoveSorter // move conatiner that stores moves in a sorted manner
{
public:
  void add(uint64_t move, int score); //add move to the container

  uint64_t getNext(); //iterator function

private:
  // number of stored moves
  unsigned int size;

  // Contains size moves with their score ordered by score
  struct
  {
    uint64_t move;
    int score;
  } entries[Position::WIDTH];
};

/*
  * Return a bitmap of all the possible next moves the do not lose in one turn.
  * A losing move is a move leaving the possibility for the opponent to win directly.
  *
  * Warning this function is intended to test position where you cannot win in one turn
  * If you have a winning move, this function can miss it and prefer to prevent the opponent
  * to make an alignment.
  
  uint64_t possibleNonLosingMoves() const {
    assert(!canWinNext());
    uint64_t possible_mask = possible();
    uint64_t opponent_win = opponent_winning_position();
    uint64_t forced_moves = possible_mask & opponent_win;
      if(forced_moves) {
        if(forced_moves & (forced_moves - 1)) // check if there is more than one forced move
          return 0;                           // the opponnent has two winning moves and you cannot stop him
        else possible_mask = forced_moves;    // enforce to play the single forced move
      }
    return possible_mask & ~(opponent_win >> 1);  // avoid to play below an opponent winning spot
  }

/////////////////////////////////////////////////////////////////////////////////////////////////////


  
 * Return a bitmask of the possible winning positions for the opponent

uint64_t opponent_winning_position() const {
  return compute_winning_position(current_position ^ mask, mask);
}

uint64_t possible() const {
  return (mask + bottom_mask) & board_mask;
}

static uint64_t compute_winning_position(uint64_t position, uint64_t mask) {
  // vertical;
  uint64_t r = (position << 1) & (position << 2) & (position << 3);

  //horizontal
  uint64_t p = (position << (HEIGHT+1)) & (position << 2*(HEIGHT+1));
  r |= p & (position << 3*(HEIGHT+1));
  r |= p & (position >> (HEIGHT+1));
  p >>= 3*(HEIGHT+1);
  r |= p & (position << (HEIGHT+1));
  r |= p & (position >> 3*(HEIGHT+1));

  //diagonal 1
  p = (position << HEIGHT) & (position << 2*HEIGHT);
  r |= p & (position << 3*HEIGHT);
  r |= p & (position >> HEIGHT);
  p >>= 3*HEIGHT;
  r |= p & (position << HEIGHT);
  r |= p & (position >> 3*HEIGHT);

  //diagonal 2
  p = (position << (HEIGHT+2)) & (position << 2*(HEIGHT+2));
  r |= p & (position << 3*(HEIGHT+2));
  r |= p & (position >> (HEIGHT+2));
  p >>= 3*(HEIGHT+2);
  r |= p & (position << (HEIGHT+2));
  r |= p & (position >> 3*(HEIGHT+2));

  return r & (board_mask ^ mask);
}
*/
