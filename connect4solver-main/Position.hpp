#pragma once

#include <cstdint>
#include <string>
#include <iostream>
using namespace std;


class Position
{
public:
    static const int WIDTH = 7;  // Width of the board
    static const int HEIGHT = 6; // Height of the board
    static const int MIN_SCORE = -(WIDTH * HEIGHT) / 2 + 3;
    static const int MAX_SCORE = (WIDTH * HEIGHT + 1) / 2 - 3;

private:
    // int board[WIDTH][HEIGHT];
    // int height[WIDTH];
    int moves;
    uint64_t current_position;
    uint64_t mask;
    static bool alignment(uint64_t pos);
    static uint64_t top_mask(int col);
    static uint64_t bottom_mask(int col);
    public: static uint64_t column_mask(int col);


    //static uint16_t maybeThisworks =  appleBottom(WIDTH, HEIGHT);
    //const static uint64_t bottom = appleBottom(WIDTH, HEIGHT);
    static uint64_t bottom;

    //const static uint64_t bottom = maybeThisworks;
    //const static uint64_t board_mask = bottom * ((1LL << HEIGHT) - 1);
    static uint64_t board_mask;

public:
    Position();
    bool canPlay(int col) const;
    void play(int col);
    unsigned int play(const char *seq);
    bool valid_xy(int x, int y) const;
    bool isWinningMove(int col) const;
    void undo(int col);
    uint64_t key() const;
    int nbMoves() const;
    void printState();
    ~Position();

    //anticipating wiining move
    uint64_t possibleNnlosingMoves() const;
    uint64_t opponent_winning_position() const;
    uint64_t possible() const;
    static uint64_t compute_winning_position(uint64_t position, uint64_t mask);

    //hope this wrks
    static uint64_t appleBottom(int width, int height);

    //check if next winning move
    uint64_t winning_position() const;
    bool canWinNext() const;
    
    /*
    static uint64_t appleBottom(int width, int height)
    {
        return width == 0 ? 0 : appleBottom(width - 1, height) | 1LL << (width - 1) * (height + 1);
    }
    */    
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
