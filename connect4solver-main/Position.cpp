
#include "Position.hpp"
#include <iostream>

// Default constructor for Position
Position::Position() : current_position(0), mask(0), moves(0)
{
    bottom = appleBottom(WIDTH, HEIGHT);
    board_mask = bottom * ((1LL << HEIGHT) - 1);
}

// Sees whether it is possible to insert in the given column or not
// @param column: the column to check
// @return: true if it is possible to insert in the given column, false otherwise
bool Position::canPlay(int col) const
{
    return (mask & top_mask(col)) == 0;
}

// Play a piece in the given column
// @param column: the column to play in
void Position::play(int col)
{
    current_position ^= mask;
    mask |= mask + bottom_mask(col);
    moves++;
}

// Plays a particular sequence of moves
// @param moves: the sequence of moves to play
// @return: number of moves played.
unsigned int Position::play(const char *seq)
{
    unsigned int i = 0;
    for (i = 0; seq[i] != '\0'; i++)
    {

        int col = seq[i] - '1';
        // if the move is invalid
        if (col < 0 || col >= WIDTH || !canPlay(col))
        {

            std::cout << "Invalid thing: " << col + 1 << std::endl;
            std::cout << seq << std::endl;
            return i;
        }
        if (isWinningMove(col))
        {
            std::cout << "Game over\n";
            exit(1);
        }
        play(col);
    }
    return i;
}
/**    
       * @return a compact representation of a position on WIDTH*(HEIGHT+1) bits.
       */
uint64_t Position::key() const
{
    return current_position + mask;
}

// Checks whether a position is on the board or not
// @param x: the x coordinate to check. 0-indexed
// @param y: the y coordinate to check. 0-indexed
// @return: true if the position is on the board, false otherwise
bool Position::valid_xy(int x, int y) const
{
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

bool Position::alignment(uint64_t pos)
{
    // horizontal
    uint64_t m = pos & (pos >> (HEIGHT + 1));
    if (m & (m >> (2 * (HEIGHT + 1))))
        return true;

    // diagonal 1
    m = pos & (pos >> HEIGHT);
    if (m & (m >> (2 * HEIGHT)))
        return true;

    // diagonal 2
    m = pos & (pos >> (HEIGHT + 2));
    if (m & (m >> (2 * (HEIGHT + 2))))
        return true;

    // vertical;
    m = pos & (pos >> 1);
    if (m & (m >> 2))
        return true;

    return false;
}

// Returns whether the given move is a winning move or not
// @param col: the column to check
// @return: true if the move is a winning move, false otherwise
bool Position::isWinningMove(int col) const
{

    uint64_t pos = current_position;
    pos |= (mask + bottom_mask(col)) & column_mask(col);
    return alignment(pos);
}

// Returns number of moves played yet
// @return: number of moves played
int Position::nbMoves() const
{
    return moves;
}

uint64_t Position::top_mask(int col)
{
    return (UINT64_C(1) << (HEIGHT - 1)) << col * (HEIGHT + 1);
}

// return a bitmask containg a single 1 corresponding to the bottom cell of a given column
uint64_t Position::bottom_mask(int col)
{
    return UINT64_C(1) << col * (HEIGHT + 1);
}

// return a bitmask 1 on all the cells of a given column
uint64_t Position::column_mask(int col)
{
    return ((UINT64_C(1) << HEIGHT) - 1) << col * (HEIGHT + 1);
}
// Destructor
Position::~Position(){};

uint64_t Position::possibleNnlosingMoves() const
{
    assert(!canWinNext());
    uint64_t possible_mask = possible();
    uint64_t opponent_win = opponent_winning_position();
    uint64_t forced_moves = possible_mask & opponent_win;
    if (forced_moves)
    {
        if (forced_moves & (forced_moves - 1)) // check if there is more than one forced move
            return 0;                          // the opponnent has two winning moves and you cannot stop him
        else
            possible_mask = forced_moves; // enforce to play the single forced move
    }
    return possible_mask & ~(opponent_win >> 1); // avoid to play below an opponent winning spot
}

uint64_t Position::opponent_winning_position() const
{
    return compute_winning_position(current_position ^ mask, mask);
}


uint64_t Position::possible() const
{
    return (mask + bottom);
}

uint64_t Position::compute_winning_position(uint64_t position, uint64_t mask)
{
    // vertical;
    uint64_t r = (position << 1) & (position << 2) & (position << 3);

    //horizontal
    uint64_t p = (position << (HEIGHT + 1)) & (position << 2 * (HEIGHT + 1));
    r |= p & (position << 3 * (HEIGHT + 1));
    r |= p & (position >> (HEIGHT + 1));
    p >>= 3 * (HEIGHT + 1);
    r |= p & (position << (HEIGHT + 1));
    r |= p & (position >> 3 * (HEIGHT + 1));

    //diagonal 1
    p = (position << HEIGHT) & (position << 2 * HEIGHT);
    r |= p & (position << 3 * HEIGHT);
    r |= p & (position >> HEIGHT);
    p >>= 3 * HEIGHT;
    r |= p & (position << HEIGHT);
    r |= p & (position >> 3 * HEIGHT);

    //diagonal 2
    p = (position << (HEIGHT + 2)) & (position << 2 * (HEIGHT + 2));
    r |= p & (position << 3 * (HEIGHT + 2));
    r |= p & (position >> (HEIGHT + 2));
    p >>= 3 * (HEIGHT + 2);
    r |= p & (position << (HEIGHT + 2));
    r |= p & (position >> 3 * (HEIGHT + 2));

    return r & (board_mask ^ mask);
}

uint64_t Position::appleBottom(int width, int height)
{
    return width == 0 ? 0 : appleBottom(width - 1, height) | 1LL << (width - 1) * (height + 1);
}

uint64_t Position::winning_position() const
{
    return compute_winning_position(current_position, mask);
}

bool Position::canWinNext() const
{
    return winning_position() & possible();
}

int Position::moveScore(uint64_t move) const
{
    return popcount(compute_winning_position(current_position | move, mask));
}

unsigned int Position::popcount(uint64_t m)
{
    unsigned int c = 0;
    for (c = 0; m; c++)
        m &= m - 1;
    return c;
}


